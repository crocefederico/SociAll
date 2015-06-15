<?php
include("config_db.php");
$connect = new mysqli("$db_host","$db_login","$db_password","$db_name");
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN"
          "http://www.w3.org/TR/html4/strict.dtd">

<HTML>
   <HEAD>
   	   <link rel="stylesheet" href="layout.css" type="text/css">
      <TITLE>SociAll-inserimento utente</TITLE>
   </HEAD>

   <BODY>
   <h3>
		<?php
			if (mysqli_connect_errno($connect)) {
			    echo "Si è verificato un problema nella connessione al DB: " . mysqli_connect_error();
			} else {
				if ($_POST['pass']!=$_POST['passconferma'])
					echo "Attenzione ! Sono state inserite due password differenti. Si prega di tornare alla pagina precedente e controllare la correttezza dei dati inseriti";
				else {
					$login = $connect->escape_string($_POST['login']);
					$pass = $connect->escape_string($_POST['pass']);
					$res = $connect->query("INSERT INTO utenti (login,pass) VALUES ('".$login."','".$pass."')");
					if(!$res)
						echo "Si è verificato un errore nell'inserimento dei dati";
					else{
						$res_fetch = $connect->query("SELECT id FROM utenti WHERE login='".$login."' AND pass='".$pass."';",MYSQLI_USE_RESULT);
						if(!res_fetch)
							echo "Impossibile trovare ID Utente";
						$row=mysqli_fetch_row($res_fetch);
						
						//la variabile $id contiene ID Utente preso dal DB
						$id=$row[0];
						
						session_start();
						$_SESSION['id']=$id;
						header("Location: inviaFoto.php");
					}
				}

			}
		?>
		</h3> <a href="registrazione.php" class="link">Torna indietro</a>
   </BODY>
</HTML>
<?php
$connect->close();
?>