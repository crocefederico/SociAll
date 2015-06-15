<?php 
header('Content-type: text/html;charset=utf-8');
session_start();
require('include/http.php');
require('include/oauth_client.php');

$message=$_POST["message"];
$message = str_replace ("à", "&agrave;", $message);
$message = str_replace ("è", "&egrave;", $message);
$message = str_replace ("ì", "&igrave;", $message);
$message = str_replace ("ò", "&ograve;", $message);
$message = str_replace ("ù", "&ugrave;", $message);

$clientFB = new oauth_client_class;
$clientFB->debug = false;
$clientFB->debug_http = true;
$clientFB->server = 'Facebook';
$clientFB->redirect_uri = 'http://sociall.local/shout.php';
$clientFB->client_id ='1598187680456122'; $application_line = __LINE__;
$clientFB->client_secret = '1d1d42da863532ddd035c30ce7d60ecb';
$clientFB->scope = 'email,publish_actions,user_friends,read_stream';
	if(($successFB = $clientFB->Initialize()))
	{
		if(($successFB = $clientFB->Process()))
		{
			if(strlen($clientFB->access_token))
			{
				
				$successFB = $clientFB->CallAPI(
					'https://graph.facebook.com/v2.3/me', 
					'GET', array(), array('FailOnAccessError'=>true), $userFB);
				$valuesFB = array(
                                                // You can no longer pre-fill the user message
                                                'message'=>$message,
                                                'description'=>'This post was submitted using PHP OAuth API'
                                        );
                                        $successFB = $clientFB->CallAPI(
                                              'https://graph.facebook.com/v2.3/me/feed', 
                                              'POST', $valuesFB, array('FailOnAccessError'=>true), $post);

		
					
				
			}

		}
		$successFB = $clientFB->Finalize($successFB);
	}
	if($clientFB->exit)
		exit;


$clientTW = new oauth_client_class;
$clientTW->debug = false;
$clientTW->debug_http = true;
$clientTW->server = 'Twitter';
$clientTW->redirect_uri = 'http://sociall.local/shout.php';
$clientTW->client_id = 'MNOXzdJz2P0cd6WVwaPEZ0jtA'; $application_line = __LINE__;
$clientTW->client_secret = '2iattm0NpFFn5cDXplamqCiKkjY8192NvBwHDrbPUAz75cf2oe';
	if(($successTW = $clientTW->Initialize()))
	{
		if(($successTW = $clientTW->Process()))
		{
			if(strlen($clientTW->access_token))
			{
					$successTW = $clientTW->CallAPI(
					'https://api.twitter.com/1.1/account/verify_credentials.json', 
					'GET', array(), array('FailOnAccessError'=>true), $userTW);		
			
					$valuesTW = array(
                                        'status'=>$message
                               		 );
	
					$successTW = $clientTW->CallAPI(
                                        'https://api.twitter.com/1.1/statuses/update.json', 
                                        'POST', $valuesTW, array('FailOnAccessError'=>true), $update);
		
			}
		}
	$successTW = $clientTW->Finalize($successTW);
	}
	if($clientTW->exit)
		exit;

if ($successTW && $successFB)

{
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<link rel="stylesheet" href="layout.css" type="text/css">
<title>SociAll</title>
</head>
<body>

<div id="corpo"> <img src="style/success.png"/> </div>
<a class="link" href="main.php">Torna alla homepage</a>


</body>
</html>
<?php
        }
        else
        {
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>OAuth client error</title>
</head>
<body>
<h1>OAuth client error</h1>
<pre>Error: <?php echo HtmlSpecialChars($clientFB->error); ?></pre>
<pre>Error: <?php echo HtmlSpecialChars($clientTW->error); ?></pre>

</body>
</html>
<?php
        }
?>





