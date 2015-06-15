<?php
include("config_db.php");
$connect = new mysqli("$db_host","$db_login","$db_password","$db_name");
$IdUtente=$_GET['id'];

if (!mysqli_connect_errno($connect)) {
	$res = $connect->query("SELECT login FROM utenti WHERE id='".$IdUtente."'");
	if($res->num_rows==1){
		session_start();
		$row=mysqli_fetch_row($res);
		//la variabile $id contiene ID Utente preso dal DB
		$_SESSION['login']=$row[0];
		header('Location: main.php');
	}
}
if (mysqli_connect_errno($connect)) {
	echo "Si è verificato un problema nella connessione al DB: " . mysqli_connect_error();
} elseif ($res->num_rows<1) {
	echo "Attenzione ! Non è stato possibile effettuare il login. Torna alla pagina<a href=\"index.php\"> precedente</a>";
}
$connect->close();
?>