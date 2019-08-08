<?php

include_once(libraries_get_path("google-api-php-client-2.2.3")  . '/vendor/autoload.php');


class Drive_Client {

  private  $client;
  private $service;

  public function __construct($application_name, $credentials, $access_token)
  {
    $client = new Google_Client();
    $client->setApplicationName($application_name);
    $client->setScopes(Google_Service_Drive::DRIVE);
    $config = json_decode($credentials, true);
    $client->setAuthConfig($config);
    $client->setAccessType('offline');
    $client->setPrompt('select_account consent');
    $client->setAccessToken(json_decode($access_token, true));

    if ($client->isAccessTokenExpired()) {
      $client->fetchAccessTokenWithRefreshToken($client->getRefreshToken());
    }
    $this->client = $client;
    $this->service = new Google_Service_Drive($client);
  }

  public function get_token(){
    return $this->client->getAccessToken();
  }

  public function provide_file_permission($fileId, $value, $type, $role){
    $newPermission = new Google_Service_Drive_Permission();
    $newPermission->setEmailAddress($value);
    $newPermission->setType($type);
    $newPermission->setRole($role);
    try {
      return $this->service->permissions->create($fileId, $newPermission);
    } catch (Exception $e) {
      print "An error occurred: " . $e->getMessage();
      return false;
    }
    return true;
  }
}
