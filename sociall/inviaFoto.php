<?php 
session_start();
?>

<html>
	<head>
		<link rel="stylesheet" href="layout.css" type="text/css">
		<title>SociAll-invioFoto</title>
	</head>

	<body>
		<div id="boxUp">
		<img src="style/upload.png" />
		</div>
		<br><br>
		
		<h4>Inserisci delle immagini in formato JPEG</h4>
		<br>
		<form name="uploader" id="uploader" action="salvaFoto.php" method="post" enctype='multipart/form-data'>
			<input type="file" onclick="attivaLoad()" multiple="multiple" name="files[]" id="file" style="color: white; width: 525px; font-size: 30px; height: 75px;">
			<input type="submit" name="send" value="Load" style="width: 200px; font-size: 30px; height: 75px;">
		</form>
		
		<script type="text/javascript">
		uploader.send.disabled=true;

		function attivaLoad(){
			uploader.send.disabled=false;
		}
		</script>
	</body>
	
</html>
