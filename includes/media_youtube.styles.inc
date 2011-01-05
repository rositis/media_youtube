<?php
// $Id$

/**
 * @file
 * Styles definitions for Media: YouTube.
 */

/**
 * Implementation of Styles module hook_styles_default_containers().
 */
function media_youtube_styles_default_containers() {
  // We append YouTube to the file containers.
  return array(
    'file' => array(
      'containers' => array(
        'media_youtube' => array(
          'class' => 'MediaYouTubeStyles',
          'name' => 'Media: YouTube',
        ),
      ),
    ),
  );
}


/**
 * Implementation of Styles module hook_styles_default_presets().
 */
function media_youtube_styles_default_presets() {
  return array(
    'file' => array(
      'containers' => array(
        'media_youtube' => array(
          'default preset' => 'linked_thumbnail',
          'styles' => array(
            'thumbnail' => array(
              'default preset' => 'linked_thumbnail',
            ),
            'square_thumbnail' => array(
              'default preset' => 'linked_square_thumbnail',
            ),
            'large' => array(
              'default preset' => 'video',
            ),
          ),
          'presets' => array(
            'unlinked_thumbnail' => array(
              array(
                'name' => 'thumbnail',
                'settings' => array(),
              ),
            ),
            'linked_thumbnail' => array(
              array(
                'name' => 'link_to_media',
                'settings' => array(),
              ),
              array(
                'name' => 'thumbnail',
                'settings' => array(),
              ),
            ),
            'linked_square_thumbnail' => array(
              array(
                'name' => 'link_to_media',
                'settings' => array(),
              ),
              array(
                'name' => 'resize',
                'settings' => array(
                  'width' => 120,
                  'height' => 120,
                ),
              ),
              array(
                'name' => 'thumbnail',
                'settings' => array(),
              ),
            ),
            'video' => array(
              array(
                'name' => 'video',
                'settings' => array(),
              ),
            ),
          ),
        ),
      ),
    ),
  );
}

class MediaYouTubeStyles extends FileStyles {
  function get_image_uri() {
    if ($image_uri = $this->get('image_uri')) {
      return $image_uri;
    }
    $object = $this->get_object();
    if ($object->uri) {
      $wrapper = file_stream_wrapper_get_instance_by_uri($object->uri);
      return $wrapper->getOriginalThumbnailPath();
    }
  }
}
