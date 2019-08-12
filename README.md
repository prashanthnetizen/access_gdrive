# Access Google Drive with Webform
### v 7.x-1.0
A Drupal 7 Module that integrates with Webform module to provide file permissions whenever the user submits the form with any email address field

## Requirements
* PHP version above 7.
* Needs [Webform](https://www.drupal.org/project/webform) module pre-installed and enabled
* Download the Google Api PHP client from [here](https://github.com/googleapis/google-api-php-client/releases/download/v2.2.3/google-api-php-client-2.2.3.zip).
* Extract the zip file and place the contents of the file under the libraries folder as in the following path:
```
/sites/all/libraries/google-api-php-client-2.2.3/
``` 
* Register your Application as a project in Google API Console and enable the Drive API.
* For your Google Application, register your domain names of your site and download the credentials.json file and keep it aside.
* Use the get_access_token.php file provided within this repository to get the token.json file for the first time.

## Installation
* Install the module normally as you would install other modules.
* open the admin configuration page of the module and copy the contents of the credentials.json file and access_token.json file.
* Provide the application name as you gave in the google api console and save the configuration.
* Now create a webform for your use. Within the webform settings for the particular form, enable the access for our new module and provide the file string ids separated by comma.
Note that each file represents a single file in your google drive.
* Now select the webform component of type E-mail address in your form and click on save.

Finally, when the form is submitted, access is enabled for the email address provided in the form.

## References
Please visit the following links to understand more about the Google API Operations:
* [Using OAuth 2.0 for Web Server Applications](https://developers.google.com/identity/protocols/OAuth2WebServer)
* [Beginners Guide to Google OAuth2.0](https://medium.com/@ashokyogi5/a-beginners-guide-to-google-oauth-and-google-apis-450f36389184)

## Licence
This project is licensed under GNU General Public License V2.

Copyright (C)  2019 Prasanth Sukhapalli
