<?php
include("config_db.php");
$connect = new mysqli("$db_host","$db_login","$db_password","$db_name");
if (!mysqli_connect_errno($connect)) {
	$login = $connect->escape_string($_POST['login']);
	$pass = $connect->escape_string($_POST['pass']);
	$res = $connect->query("SELECT * FROM utenti WHERE login='".$login."' AND pass='".$pass."'");
	if($res->num_rows==1){
		session_start();
		$_SESSION['login']=$login;
		header('Location: main.php');
	}
}
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN"
          "http://www.w3.org/TR/html4/strict.dtd">

<HTML>
   <HEAD>
   		<link rel="stylesheet" href="layout.css" type="text/css">
      <TITLE>SociAll-login</TITLE>
   </HEAD>

   <BODY>
   <h3>
		<?php
			if (mysqli_connect_errno($connect)) {
			    echo "Si è verificato un problema nella connessione al DB: " . mysqli_connect_error();
			} elseif ($res->num_rows<1) {
				echo "Attenzione ! Sono stati inseriti dati errati. Torna alla pagina di <a href=\"index.php\">login</a>";
			}
		?>
	</h3>
   </BODY>
</HTML>
<?php
$connect->close();
?>
