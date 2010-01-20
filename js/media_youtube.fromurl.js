// $Id$

/**
 *  @file
 *  Create the 'YouTube' tab for the WYSIWYG plugins.
 */

(function ($) {
  namespace('Drupal.media.browser.plugin');

  Drupal.media.browser.plugin.media_youtube = function(mediaBrowser, options) {
    return {
      init: function() {
        tabset = mediaBrowser.getTabset();
        tabset.tabs('add', '#media_youtube', 'YouTube');
        mediaBrowser.listen('tabs.tabSelected', function (e, id) {
          if (id == 'media_youtube') {
            mediaBrowser.getContentArea().load(Drupal.settings.basePath + 'media/add/media_youtube?destination=' + window.location.href +' form#media-youtube-add');
          }
        });
      }
    }
  };

  // For now, I guess self registration makes sense.
  // Really though, we should be doing it via drupal_add_js and some settings
  // from the drupal variable.
  //@todo: needs a review.
  Drupal.media.browser.register('media_youtube', Drupal.media.browser.plugin.media_youtube, {});
})(jQuery);
