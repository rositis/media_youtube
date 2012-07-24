<?php

/**
 * @file media_youtube/includes/themes/media_youtube.theme.inc
 *
 * Theme and preprocess functions for Media: YouTube.
 */

/**
 * Preprocess function for theme('media_youtube_video').
 */
function media_youtube_preprocess_media_youtube_video(&$variables) {

  // Build the URI.
  $wrapper = file_stream_wrapper_get_instance_by_uri($variables['uri']);
  $parts = $wrapper->get_parameters();
  $variables['video_id'] = check_plain($parts['v']);

  // Parse options and build the query string. Only add the option to the query
  // array if the option value is not default. Be careful, depending on the
  // wording in media_youtube.formatters.inc, TRUE may be query=0.
  // @see https://developers.google.com/youtube/player_parameters#Parameters
  $query = array();

  // Make css z-index work with flash object. Must be the first parameter.
  $query['wmode'] = 'opaque';
  
  // These queries default to 0. If the option is true, set value to 1.
  foreach (array('autoplay', 'enablejsapi', 'loop', 'modestbranding') as $option) {
    if ($variables['options'][$option]) {
      $query[$option] = 1;
    }
  }

  // Currently, loop only works with a playlist. Make fake playlist out of a
  // single video.
  // @see https://developers.google.com/youtube/player_parameters#loop
  if ($variables['options']['loop']) {
    $query['playlist'] = $variables['video_id'];
  }

  // These queries default to 1. If the option is false, set value to 0.
  foreach (array('rel', 'showinfo') as $option) {
    if (!$variables['options'][$option]) {
      $query[$option] = 0;
    }
  }

  // These queries default to 1. Option wording is reversed, so if the option
  // is true, set value to 0.
  if ($variables['options']['controls']) {
    $query['controls'] = 0;
  }
  // Reverse the reversed option so that it makes sense in the tpl.
  if ($variables['options']['controls'] = 1) {
    $variables['options']['controls'] = 0;
  }
  else {
    $variables['options']['controls'] = 1;
  }

  // Strings.
  if ($variables['options']['theme'] != 'dark') {
    $query['theme'] = $variables['options']['theme'];
  }
  if ($variables['options']['color'] != 'red') {
    $query['color'] = $variables['options']['color'];
  }
  if ($variables['options']['autohide'] != '2') {
    $query['autohide'] = $variables['options']['autohide'];
  }

  // Non-query options.
  if ($variables['options']['nocookie']) {
    $url_base = 'youtube-nocookie.com';
  }
  else {
    $url_base = 'youtube.com';
  }

  // Add some options as their own template variables.
  foreach (array('width', 'height') as $themevar) {
    $variables[$themevar] = $variables['options'][$themevar];
  }

  // Build the iframe URL with options query string.
  // Use https as default protocol instead of relative protocol to maintain
  // compatibility with content emails, rss, and https sites.
  // @see http://drupal.org/node/1368818
  $variables['url'] = url('https://www.' . $url_base . '/embed/' . $variables['video_id'], array('query' => $query, 'external' => TRUE, 'https' => TRUE));
}

/**
 * Styles
 */
function theme_media_youtube_field_formatter_styles($variables) {
  $element = $variables['element'];
  $style = $variables['style'];
  $variables['file'] = $element['#item'];
  $variables['uri'] = $variables['file']['uri'];
  $variables['style_name'] = $style['name'];
  return theme('media_youtube_embed', $variables);
}

/**
 * Preview for Styles UI.
 */
function theme_media_youtube_preview_style($variables) {
  $variables['uri'] = media_youtube_variable_get('preview_uri');
  $variables['field_type'] = 'file';
  $variables['object'] = file_uri_to_object($variables['uri']);

  return theme('styles', $variables);
}

/**
 * NOTE: Deprecated with Styles version 2.
 */
function theme_media_youtube_styles($variables) {
  $style = $variables['style'];
  $variables['file'] = $variables['object'];
  $variables['uri'] = $variables['object']->uri;
  $variables['style_name'] = $style['name'];
  return theme('media_youtube_embed', $variables);
}

/**
 * @todo: get this working
 *
 * This code is for embedding videos in WYSIYWG areas, not currently working.
 * NOTE: Deprecated with Styles version 2.
 */
function theme_media_youtube_embed($variables) {
  $preset_name = $variables['preset_name'];
  $preset = styles_containers_available_styles('file', 'media_youtube', $preset_name);
  $output = '';
  if (!empty($preset)) {
    // Build the URL for display.
    $uri = $variables['uri'];
    $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
    $parts = $wrapper->get_parameters();

    $fullscreen_value = $autoplay = 'false';
    $in_browser = $thumbnail = FALSE;

    foreach ($preset['effects'] as $effect) {
      switch ($effect['name']) {
        case 'autoplay':
          $autoplay = $effect['data']['autoplay'] ? 'true' : 'false';
          break;
        case 'resize':
          $width = $effect['data']['width'];
          $height = $effect['data']['height'];
          break;
        case 'fullscreen':
          $fullscreen_value = $effect['data']['fullscreen'] ? 'true' : 'false';
          break;
        case 'thumbnail':
          $thumbnail = $effect['data']['thumbnail'];
      }
    }
    if (isset($variables['object']->override)) {
      $override = $variables['object']->override;
      if (isset($override['width'])) {
        $width = $override['width'];
      }
      if (isset($override['height'])) {
        $height = $override['height'];
      }
      if (isset($override['wysiwyg'])) {
        $thumbnail = TRUE;
      }
      if (isset($override['browser']) && $override['browser']) {
        $in_browser = TRUE;
        $thumbnail = TRUE;
      }
    }
    $width = isset($width) ? $width : media_youtube_variable_get('width');
    $height = isset($height) ? $height : media_youtube_variable_get('height');
    $video_id = check_plain($parts['v']);
    if ($thumbnail) {
      // @todo Clean this up.
      $image_variables = array(
        'path' => $wrapper->getOriginalThumbnailPath(),
        'alt' => $variables['alt'],
        'title' => $variables['title'],
        'getsize' => FALSE,
      );
      if (isset($preset['image_style'])) {
        $image_variables['path'] = $wrapper->getLocalThumbnailPath();
        $image_variables['style_name'] = $preset['image_style'];
        $output = theme('image_style', $image_variables);
      }
      else {
        // We need to add this style attribute here so that it doesn't get lost
        // If you resize a video in a node, save it, edit it, but don't adjust
        // the sizing of the video while editing, the size will revert to the
        // default.  Adding the specific size here retains the original resizing
        $WYSIWYG = isset($variables['object']->override['style']) ? $variables['object']->override['style'] : '';
        $image_variables['attributes'] = array('width' => $width, 'height' => $height, 'style' => $WYSIWYG);
        $output = theme('image', $image_variables);
      }
      if ($in_browser) {
        // Add an overlay that says 'YouTube' to media library browser thumbnails.
        $output .= '<span />';
      }
    }
    else {
      $output = theme('media_youtube_video', array('uri' => $uri, 'width' => $width, 'height' => $height, 'autoplay' => ($autoplay == 'true' ? TRUE : NULL), 'fullscreen' => ($fullscreen_value == 'true' ? TRUE : NULL)));
    }
  }
  return $output;
}
