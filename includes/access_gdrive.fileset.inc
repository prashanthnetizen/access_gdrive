<?php

/**
 * @file
 * This file validates submits and stores the values of the form.
 */

/**
 * Implements the Admin Configuration form to store the credentials and tokens.
 *
 * @param array $form
 *   Specifes contents of form.
 * @param array $form_state
 *   Specifies state of the form.
 *
 * @return mixed
 *   Returns form elements to be rendered
 */
function access_gdrive_admin_form(array $form, array &$form_state) {
  $result = db_query("SELECT * FROM {access_gdrive}")->fetchAssoc();
  $form['credentials'] = array(
    '#title' => 'Google Application Credentials',
    '#description' => 'Copy the contents from Credential json file generated in Google API console for your project',
    '#type' => 'textarea',
    '#required' => TRUE,
    '#default_value' => $result['credentials'],
  );
  $form['access_token'] = array(
    '#title' => 'Access Token',
    '#description' => 'Copy contents from Token json file generated using OAuth2.0 protocol',
    '#type' => 'textarea',
    '#required' => TRUE,
    '#default_value' => $result['access_token'],
  );
  $form['app_name'] = array(
    '#title' => 'Google App Name',
    '#description' => 'Google Application Name or Project Name',
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => $result['app_name'],
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit Configuration',
  );
  return $form;
}

/**
 * Implements the form handler for inserting admin form entries.
 *
 * @param array $form
 *   Specifies the form.
 * @param array $form_state
 *   Specifies state of the form.
 *
 * @throws Exception
 */
function access_gdrive_admin_form_submit(array $form, array &$form_state) {
  $delete = db_delete('access_gdrive')->execute();
  $id = db_insert('access_gdrive')->fields(array(
    'credentials' => $form_state['values']['credentials'],
    'access_token' => $form_state['values']['access_token'],
    'app_name' => $form_state['values']['app_name'],
  ))->execute();
  drupal_set_message(t("Your Entry has been added Successfully"));
}

/***
 * Implements the File ID edit form for each webform created.
 *
 * @param array $form
 *   Specifies the form.
 * @param array $form_state
 *   Specifies the state of the form.
 * @param array $node
 *   Specifies the Node.
 *
 * @return mixed
 *   returns the form elements to be rendered.
 */
function access_gdrive_edit_form(array $form, array &$form_state, array $node) {
  module_load_include('inc', 'webform', 'includes/webform.components');
  $result = db_query("SELECT * FROM {access_gdrive_files} WHERE nid = :nid", array(":nid" => $node->nid))->fetchAssoc();
  $form['enable_access'] = array(
    '#title' => 'Enable Access',
    '#description' => t('Check this checkbox to enable this feature'),
    '#type' => 'checkbox',
    '#required' => TRUE,
    '#default_value' => $result['enable_access'],
  );
  $form['nid'] = array(
    '#type' => 'hidden',
    '#default_value' => $node->nid,
  );
  $form['files'] = array(
    '#title' => 'File ID Strings',
    '#description' => t('provide file id strings separated by commas, no white spaces in between'),
    '#type' => 'textarea',
    '#required' => TRUE,
    '#default_value' => $result['file_ids'],
  );
  $form['cid'] = array(
    '#title' => 'Email Component',
    '#description' => t('Select the component which bears the Email Value.'),
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => webform_component_list($node, 'email_address', FALSE),
    '#default_value' => $result['cid'],
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );
  return $form;
}

/**
 * Implements the Submit Handler for the Edit form.
 *
 * @param array $form
 *   Specifies the form.
 * @param array $form_state
 *   Specifies the state of the form.
 */
function access_gdrive_edit_form_submit(array $form, array &$form_state) {
  try {
    $num_deleted = db_delete('access_gdrive_files')
      ->condition('nid', $form_state['values']['nid'])
      ->execute();
    $id = db_insert('access_gdrive_files')->fields(array(
      'nid' => $form_state['values']['nid'],
      'enable_access' => $form_state['values']['enable_access'],
      'file_ids' => $form_state['values']['files'],
      'cid' => $form_state['values']['cid'],
    ))->execute();
  }
  catch (Exception $e) {
    watchdog_exception("access_gdrive", $e->getCode(), $e->getMessage());
  }
  drupal_set_message(t("Your Entry has been added Successfully"));
}
