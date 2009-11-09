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
  private $base_url = 'http://youtube.com/watch';
}
