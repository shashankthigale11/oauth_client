<?php

function oauth_client_config($form, &$formstate)
{
  global $base_url;

  $oauth_client_callback_uri = $base_url."/?q=oauth_login";
  config_set('oauth_client.settings','oauth_client_callback_uri',$oauth_client_callback_uri);

  $app_values = config_get('oauth_client.settings','oauth_client_app_values');

  $form['oauth_client_select_app'] = array(
    '#type' => 'select',
    '#title' => t('Select Application'),
    '#options' => array(
      'Select' => t('- Select -'),
      'Azure AD' => t('Azure AD'),
      'Okta' => t('Okta'),
    ),
    '#default_value' => $app_values['app_name'],
  );

  $form['oauth_callback'] = array(
    '#type' => 'textfield',
    '#title' => t('Callback URI'),
    '#default_value' => $oauth_client_callback_uri,
    '#disabled' => true,
  );

  $form['oauth_client_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Client ID'),
    '#default_value' => $app_values['client_id'],
  );

  $form['oauth_client_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Client Secret'),
    '#default_value' => $app_values['client_secret'],
  );

  $form['oauth_client_scope'] = array(
    '#type' => 'textfield',
    '#title' => t('Scope'),
    '#default_value' => $app_values['scope'],
  );

  $form['oauth_client_authorization_ep'] = array(
    '#type' => 'textfield',
    '#title' => t('Authorization Endpoint'),
    '#default_value' => $app_values['authorization_ep'],
    '#maxlength' => 1048,
  );

  $form['oauth_client_token_ep'] = array(
    '#type' => 'textfield',
    '#title' => t('Access Token Endpoint'),
    '#default_value' => $app_values['token_ep'],
    '#maxlength' => 1048,
  );

  $form['oauth_client_user_info_ep'] = array(
    '#type' => 'textfield',
    '#title' => t('UserInfo Endpoint'),
    '#default_value' => $app_values['user_info_ep'],
    '#maxlength' => 1048,
  );

  $form['oauth_client_email_attribute'] = array(
    '#type' => 'textfield',
    '#title' => t('Email Attribute'),
    '#default_value' => $app_values['email_attribute'],
    '#maxlength' => 1048,
  );

  $form['oauth_client_enable_sso'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable SSO Login'),
    '#default_value' => $app_values['enable_sso'],
  );

  $form['oauth_client_config_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Configuration'),
    '#submit' => array('oauth_client_save_config'),
  );

  $form['oauth_client_test_config_button'] = array(
    '#id' => 'oauth_client_test_config_button',
    '#markup' => '<a class="button button--primary" onclick="testConfig(\'' . getTestUrl() . '\'); ">'.'Test Configuration</a>'
  );

  return $form;
}

function oauth_client_save_config($form, &$form_state){

  $form_values = $form_state['input'];

  $app_values = config_get('oauth_client.settings','oauth_client_app_values');
  if(!is_array($app_values))
    $app_values = array();

  $app_values['client_id'] = $form_values['oauth_client_client_id'];
  $app_values['client_secret'] = $form_values['oauth_client_client_secret'];
  $app_values['app_name'] = $form_values['oauth_client_select_app'];
  $app_values['scope'] = $form_values['oauth_client_scope'];
  $app_values['authorization_ep'] = $form_values['oauth_client_authorization_ep'];
  $app_values['token_ep'] = $form_values['oauth_client_token_ep'];
  $app_values['user_info_ep'] = $form_values['oauth_client_user_info_ep'];
  $app_values['email_attribute'] = $form_values['oauth_client_email_attribute'];
  $app_values['enable_sso'] = $form_values['oauth_client_enable_sso'];

  config_set('oauth_client.settings', 'oauth_client_app_values', $app_values);
  backdrop_set_message(t('Configurations saved successfully. Please click on the <b>Test Configuration</b> button to test the connection.'));

}

function getTestUrl() {
  global $base_url;
  return $base_url.'/?q=testConfig';
}

?>
