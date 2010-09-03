<?php
// $Id$

/**
 *  @file
 *  Create a YouTube Stream Wrapper class for the Media/Resource module.
 */

/**
 *  Create an instance like this:
 *  $youtube = new ResourceYouTubeStreamWrapper('youtube://?v=[video-code]');
 */
class MediaYouTubeStreamWrapper extends MediaReadOnlyStreamWrapper {
  protected $base_url = 'http://youtube.com/watch';
  
  function getTarget($f) {
    return FALSE;  
  }
  
  static function getMimeType($uri, $mapping = NULL) {
    return 'video/youtube';
  }
}
