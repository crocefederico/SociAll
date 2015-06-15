<?php
session_start();

$uploaddir="utenti/".$_SESSION['id']."/";	//va sostituito con il nome ad hoc della cartella per l'utente

if (!mkdir($uploaddir, 0777, true)) {
    die('Si è verificato un errore, si prega di riprovare');
}
$lista = $_FILES['files']['tmp_name'];
if(sizeof($lista)==0)
	die("ERRORE");
else{
	foreach ($lista as $nome_immagine) {
		$file=basename($nome_immagine).".jpg";
		$path=$uploaddir.$file;
		if(!move_uploaded_file($nome_immagine, $path))
			echo "Failed to upload $nome_immagine";
	}
		$command = "./Face_Recog_Server --train "."$uploaddir"." ".$_SESSION['id'];
	
		echo "Registrazione effettuata con successo !";
		exec($command,$esito);
		header("Location: registra_ok.php");
}
?>