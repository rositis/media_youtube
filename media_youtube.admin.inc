<?php
// $Id$

/**
 *  @file
 *  Administrative page callbacks for Media: YouTube.
 */

/**
 *  Callback for /media/add/media_youtube and
 *  /admin/content/media/add/media_youtube.
 */
function media_youtube_add($form, &$form_state = array(), $redirect = NULL) {
  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => 'URL',
    '#description' => 'Input the URL of the desired YouTube video page.',
  );

  $form['redirect'] = array(
    '#type' => 'value',
    '#value' => $redirect,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}

/**
 *  Validation for media_youtube_add().
 */
function media_youtube_add_validate($form, &$form_state) {
  if (!preg_match('@youtube\.com/watch\?v=([^"\& ]+)@i', $form_state['values']['url'], $matches)) {
    form_set_error('url', t('Please submit a valide YouTube video URL.'));
  }
}

/**
 *  Submission for media_youtube_add().
 *
 *  This will create a file object for the YouTube video.
 */
function media_youtube_add_submit($form, &$form_state) {
  $uri = media_flickr_media_parse($form_state['values']['url']);

  $defaults = array (
    'display' => TRUE,
  );

  // @TODO: This won't work for YouTube and many other streams.
//   copy($url, $destination);

  $file = file_uri_to_object($uri);

  file_save($file);

  if ($file) {
    $form_state['redirect'] = 'media/' . $file->fid . '/edit';
    field_attach_submit('media', $file, $form, $form_state);
    // Make a copy of the file object to use as the media object
    // (file is a field of media and the base table). This is weird.
    $media = clone($file);
    $file->file = array();
    $file->file[LANGUAGE_NONE] = array();
    $file->file[LANGUAGE_NONE][0] = (array)$file + $defaults;
    $file->is_new = TRUE;
    field_attach_insert('media', $file);
  }
  else {
    drupal_set_message(t('An error occurred and no file was saved.'), 'error');
  }

  $form_state['redirect'] = !empty($form_state['values']['redirect']) ? $form_state['values']['redirect'] : 'media/' . $file->fid . '/edit';
}
