<?php

/**
 * @file
 * Class DriveClient handles authentication and permission operations.
 */

include_once libraries_get_path("google-api-php-client-2.2.3") . '/vendor/autoload.php';
/**
 * Create DriveClient class.
 */
class DriveClient {
  /**
   * Client Object of this class instance.
   *
   * @var client
   */
  private $client;
  /**
   * Google Drive Service Variable.
   *
   * @var service
   */
  private $service;

  /**
   * Drive_Client constructor to create a Authenticated Google Client.
   *
   * This utilizes Access Token and Credential Values via OAuth2.0 protocol.
   *
   * @param string $application_name
   *   The Name of the Application in Google Api console.
   * @param string $credentials
   *   The Credentials json Associative Array.
   * @param string $access_token
   *   The Access Token json Associative Array.
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
   * Returns the newly refreshed access token.
   *
   * @return mixed
   *   returns Newly generated Access Token for the instance.
   */
  public function getToken() {
    return $this->client->getAccessToken();
  }

  /**
   * Function to provide file permissions to individual files.
   *
   * @param string $fileId
   *   File ID string of the file in Google Drive.
   * @param string $value
   *   Email Address Value.
   * @param string $type
   *   Reader or Writer Type.
   * @param string $role
   *   User or Group Role.
   *
   * @return bool
   *   This boolean returns completion status of the function
   */
  public function provideFilePermission($fileId, $value, $type, $role) {
    $newPermission = new Google_Service_Drive_Permission();
    $newPermission->setEmailAddress($value);
    $newPermission->setType($type);
    $newPermission->setRole($role);
    try {
      return $this->service->permissions->create($fileId, $newPermission);
    }
    catch (Exception $e) {
      print "An error occurred: " . $e->getMessage();
      return FALSE;
    }
    return TRUE;
  }

}
