<?php

/**
 * @file
 * Class DriveClient handles authentication and permission operations
 *
 */

include_once libraries_get_path("google-api-php-client-2.2.3") . '/vendor/autoload.php' ;


class DriveClient {

  private $client;
  private $service;

  /**
   * Drive_Client constructor to create a Authenticated Google Client with the Access Token and Credential Values
   * using OAuth2.0 protocol
   * @param $application_name
   * @param $credentials
   * @param $access_token
   *
   */

  public function __construct($application_name, $credentials, $access_token) {
    $client = new Google_Client();
    $client->setApplicationName($application_name);
    $client->setScopes(Google_Service_Drive::DRIVE);
    $config = json_decode($credentials, TRUE);
    $client->setAuthConfig($config);
    $client->setAccessType('offline');
    $client->setPrompt('select_account consent');
    $client->setAccessToken(json_decode($access_token, TRUE));

    if ($client->isAccessTokenExpired()) {
      $client->fetchAccessTokenWithRefreshToken($client->getRefreshToken());
    }
    $this->client = $client;
    $this->service = new Google_Service_Drive($client);
  }

  /**
   * Returns the newly refreshed access token
   *
   * @return mixed
   *
   */

  public function get_token() {
    return $this->client->getAccessToken();
  }

  /**
   * Function to provide file permissions to individual files
   *
   * @param $fileId
   * @param $value
   * @param $type
   * @param $role
   * @return bool
   */

  public function provide_file_permission($fileId, $value, $type, $role) {
    $newPermission = new Google_Service_Drive_Permission();
    $newPermission->setEmailAddress($value);
    $newPermission->setType($type);
    $newPermission->setRole($role);
    try {
      return $this->service->permissions->create($fileId, $newPermission);
    } catch (Exception $e) {
      print "An error occurred: " . $e->getMessage();
      return FALSE;
    }
    return TRUE;
  }
}
