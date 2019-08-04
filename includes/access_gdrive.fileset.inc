<?php

function access_gdrive_admin_form($form, &$form_state){
  $form['credentials'] = array(
    '#title' => 'Google Application Credentials',
    '#description' => 'Credential json file generated in Google API console for your project',
    '#type' => 'file',
    '#required' => TRUE,
  );
  $form['access_token'] = array(
    '#title' => 'Access Token',
    '#description' => 'Token json file generated using OAuth2.0 protocol',
    '#type' => 'file',
    '#required' => TRUE,
  );
  $form['app_name'] = array(
    '#title' => 'Google App Name',
    '#description' => 'Google Application Name or Project Name',
    '#type' => 'textfield',
    '#required' => TRUE,
  );
  return system_settings_form($form);
}
