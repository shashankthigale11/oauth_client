<?php

function oauth_client_initiateLogin() {
  global $base_url;
  $_SESSION['redirect_url'] = $_SERVER['HTTP_REFERER'];
  $app_values = config_get('oauth_client.settings', 'oauth_client_app_values');
  $app_name = $app_values['app_name'];
  $client_id = $app_values['client_id'];
  $scope = $app_values['scope'];
  $authorizationUrl = $app_values['authorization_ep'];
  $callback_uri = $base_url."/?q=oauth_login";
  $state = base64_encode($app_name);
  if (str_contains($authorizationUrl, '?')) {
    $authorizationUrl =$authorizationUrl. "&client_id=".$client_id."&scope=".$scope."&redirect_uri=".$callback_uri."&response_type=code&state=".$state;
  }
  else {
    $authorizationUrl =$authorizationUrl. "?client_id=".$client_id."&scope=".$scope."&redirect_uri=".$callback_uri."&response_type=code&state=".$state;
  }
  $_SESSION['oauth2state'] = $state;
  $_SESSION['appname'] = $app_name;
  header('Location: ' . $authorizationUrl);
  backdrop_goto($authorizationUrl);
}

function getAccessToken($tokenendpoint, $grant_type, $clientid, $clientsecret, $code, $redirect_url, $send_headers, $send_body) {

  $fields = array(
    'headers' => array(
      'Accept' => 'application/json',
      'Content-Type' => 'application/x-www-form-urlencoded',
    ),
    'data' =>  'redirect_uri=' . urlencode($redirect_url) . '&grant_type=' . $grant_type . '&client_id=' . urlencode($clientid) . '&client_secret=' . urlencode($clientsecret) . '&code=' . $code,
    'verify' => FALSE,
    'method' => 'POST'
  );

  $response = backdrop_http_request($tokenendpoint,$fields);
  $content = json_decode($response->data, true);

  if (isset($content["error"])) {
    if (is_array($content["error"])) {
      $content["error"] = $content["error"]["message"];
    }
    exit($content["error"]);
  }
  else if(isset($content["error_description"])){
    exit($content["error_description"]);
  } else if(isset($content["access_token"])) {
    $access_token = $content["access_token"];
  } else {
    echo "<b>Response : </b><br>";print_r($content);echo "<br><br>";
    exit('Invalid response received from OAuth Provider. Contact your administrator for more details.');
  }
  return $access_token;
}

function getResourceOwner($user_info_ep, $access_token){

  $fields = array(
    'headers' => array(
      'Authorization' => 'Bearer ' . $access_token
    ),
    'verify' => FALSE,
  );

  $response = backdrop_http_request($user_info_ep, $fields);
  return json_decode($response->data, true);

}
