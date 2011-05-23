<?php

/**
 * @file media_youtube/includes/media_youtube.styles.inc
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
          'name' => 'media_youtube',
          'label' => t('YouTube'),
          'preview' => 'media_youtube_preview_style',
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
            'original' => array(
              'default preset' => 'video',
            ),
            'thumbnail' => array(
              'default preset' => 'linked_thumbnail',
            ),
            'square_thumbnail' => array(
              'default preset' => 'linked_square_thumbnail',
            ),
            'medium' => array(
              'default preset' => 'linked_medium',
            ),
            'large' => array(
              'default preset' => 'large_video',
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
                'name' => 'image_style',
                'settings' => array(
                  'image_style' => 'square_thumbnail',
                ),
              ),
              array(
                'name' => 'thumbnail',
                'settings' => array(),
              ),
            ),
            'linked_medium' => array(
              array(
                'name' => 'link_to_media',
                'settings' => array(),
              ),
              array(
                'name' => 'image_style',
                'settings' => array(
                  'image_style' => 'medium',
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
            'large_video' => array(
              array(
                'name' => 'resize',
                'settings' => array(
                  'width' => 480,
                  'height' => 360,
                ),
              ),
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
