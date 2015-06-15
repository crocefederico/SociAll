<?php
	define('UPLOAD_DIR', 'uploads/');
	include("config_db.php");
	
	$img = $_POST['imgData'];
	$img = str_replace('data:image/jpeg;base64,', '', $img);
	$img = str_replace(' ', '+', $img);
	$data = base64_decode($img);
	$file =  UPLOAD_DIR . uniqid() . '.jpg';

	//Salvataggio dell'immagine
	$success = file_put_contents($file, $data);
	
	$command = "./Face_Recog_Server --recog "."$file";
	if($success==0)
		echo 'ERROR:404';
	else{
		exec($command,$esito);
		//Invio Id Utente
		echo $esito[0];
	}
?>