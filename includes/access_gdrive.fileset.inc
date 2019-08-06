<?php

function access_gdrive_admin_form($form, &$form_state){
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
    '#value' => 'Submit Configuration'
  );
  return $form;
}

/**
 * Implements the form handler for inserting admin form entries
 *
 * @param $form
 * @param $form_state
 * @throws Exception
 */

function access_gdrive_admin_form_submit($form, &$form_state){
  $delete = db_delete('access_gdrive')->execute();
  $id = db_insert('access_gdrive')->fields(array(
    'credentials' => $form_state['values']['credentials'],
    'access_token' => $form_state['values']['access_token'],
    'app_name' => $form_state['values']['app_name'],
  ))->execute();
  drupal_set_message("Your Entry has been added Successfully");
}


function access_gdrive_edit_form($form, &$form_state, $node){
  module_load_include('inc', 'webform', 'includes/webform.components');
  $result = db_query("SELECT * FROM {access_gdrive_files} WHERE nid = :nid", array(":nid" => $node->nid))->fetchAssoc();
  $form['enable_access'] = array(
    '#title' => 'Enable Access',
    '#description' => 'Check this checkbox to enable this feature',
    '#type' => 'checkbox',
    '#required' => FALSE,
    '#default_value' => $result['enable_access'],
  );
  $form['nid'] = array(
    '#type' => 'hidden',
    '#default_value' => $node->nid,
  );
  $form['files'] = array(
    '#title' => 'File ID Strings',
    '#description' => 'provide file id strings separated by commas, no white spaces in between',
    '#type' => 'textarea',
    '#required' => FALSE,
    '#default_value' => $result['file_ids'],
  );
  $form['component_value'] = array(
    '#title' => 'Email Component',
    '#description' => 'Select the component which bears the Email Value.',
    '#type' => 'select',
    '#required' => FALSE,
    '#options'  =>webform_component_list($node, 'email_address', FALSE),
    '#default_value' => $result['component_value'],
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save'
  );
  return $form;
}

function access_gdrive_edit_form_submit($form, &$form_state){
  try {
    $num_deleted = db_delete('access_gdrive_files')
      ->condition('nid', $form_state['values']['nid'])
      ->execute();
    $id = db_insert('access_gdrive_files')->fields(array(
      'nid' => $form_state['values']['nid'],
      'enable_access' => $form_state['values']['enable_access'],
      'file_ids' => $form_state['values']['files'],
      'component_value' => $form_state['values']['component_value'],
    ))->execute();
  } catch (Exception $e) {

  }
  drupal_set_message("Your Entry has been added Successfully");
}
