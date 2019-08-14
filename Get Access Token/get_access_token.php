<?php

/**
 * @file
 * Script to get the Access Token Json file. Please make sure you have the necessary SSL CA certificates installed for both php and drupal.
 *
 */

// Path to the Libraries in your local installation. You need to change this.
require_once 'D:/WAMP/www/drupal/sites/all/libraries/google-api-php-client-2.2.3/vendor/autoload.php';

echo "Session started for fetching the Access Token";

$client = new Google_Client();
// Replace with your Application Name
$client->setApplicationName('Quickstart');
$client->setScopes(Google_Service_Drive::DRIVE);
try {
  // Use your credentials.json obtained from Google Api console
  $client->setAuthConfig('credentials.json');
} catch (Google_Exception $e) {

}
$client->setAccessType('offline');
$client->setPrompt('select_account consent');
// Load previously authorized token from a file, if it exists.
// The file token.json stores the user's access and refresh tokens, and is
// created automatically when the authorization flow completes for the first
// time.
$tokenPath = 'token.json';
if (file_exists($tokenPath)) {
  $accessToken = json_decode(file_get_contents($tokenPath), TRUE);
  $client->setAccessToken($accessToken);
}
// If there is no previous token or it's expired.
if ($client->isAccessTokenExpired()) {
  // Refresh the token if possible, else fetch a new one.
  if ($client->getRefreshToken()) {
    echo "token refresh operation";
    $client->fetchAccessTokenWithRefreshToken($client->getRefreshToken());
  } else {
    // Request authorization from the user.
    $authUrl = $client->createAuthUrl();
    printf("Open the following link in your browser:\n%s\n", $authUrl);
    print 'Enter verification code: ';
    $authCode = trim(fgets(STDIN));
    // Exchange authorization code for an access token.
    $accessToken = $client->fetchAccessTokenWithAuthCode($authCode);
    $client->setAccessToken($accessToken);
    // Check to see if there was an error.
    if (array_key_exists('error', $accessToken)) {
      throw new Exception(join(', ', $accessToken));
    }
  }
  // Save the token to a file.
  if (!file_exists(dirname($tokenPath))) {
    mkdir(dirname($tokenPath), 0700, TRUE);
  }
  file_put_contents($tokenPath, json_encode($client->getAccessToken()));
}
