<!DOCTYPE html>
<html>
    <head>
    	<link rel="stylesheet" href="layout.css" type="text/css">
       <title>SociAll-login-con-webcam</title>
    </head>
    
    <body>
    <img src="style/riconoscimento_facciale.png" />
    <br><br><br>
    	<div id="page">
    	<div id="webcam_img">
        <video autoplay="true" id="video" width="640"></video>
         <a href="login_manuale.php" class="link">Oppure inserisci le credenziali a mano</a>
        </div>
        <div id="box2">
        <br>
        <br>
        <br>
        <button id="photo" onclick="takePhoto();"><img src="style/scatta.png"/></button>
        <br>
        <br>
        <button name="snd" id="send" onclick="sendPhoto();"><img src="style/submit.png"/></button>
        </div>
        <div id="canv">
        <canvas id="canvas"></canvas>
        <h4>
        Scatta la foto quando sei pronto e premi submit per autenticarti
        </h4>
        </div>
        </div>
        <br>
       
        
        <script>
        	var dataAsURL;
            var video = document.getElementById('video');

            //Cross Browser user media function
            navigator.getMedia = (navigator.getUserMedia ||
                    navigator.webkitGetUserMedia ||
                    navigator.mozGetUserMedia);

            var options = {
                video: true,
                audio: false
            };
            var onSuccess = function(stream) {
                //Firefox
                if (navigator.mozGetUserMedia) {
                     video.mozSrcObject = stream;
                } else {
                     //Chrome,Opera
                     var vendorURL = window.URL || window.webkitURL;
                     video.src = vendorURL.createObjectURL(stream);
                }
            };

            var onError = function(err) {
                console.log("An error occured! " + err);
            };

            navigator.getMedia(options, onSuccess, onError);
            
            function takePhoto() {
                var canvas = document.getElementById('canvas');
                
                var canvasWidth = 320;
                var canvasHeight = video.videoHeight / (video.videoWidth / canvasWidth);
                canvas.setAttribute('width', canvasWidth);
                canvas.setAttribute('height', canvasHeight);
                canvas.getContext('2d').drawImage(video, 0, 0, canvasWidth, canvasHeight);

                //salva il context del canvas nella variabile dataAsURL
                dataAsURL = canvas.toDataURL("image/jpeg");
            }
            
            function sendPhoto(){
                //Fa una richiesta AJAX a test.php che restituirà l'ID dell'utente, oppure Unknown
				var xmlhttp = new XMLHttpRequest();
				xmlhttp.open("POST","test.php",false);
				xmlhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
				xmlhttp.send("imgData="+dataAsURL);

				var result=xmlhttp.responseText;

				if(result=="ERROR:404" || result==""){
					alert("Errore, si prega di riprovare");
				}
				else{
					if(result != "Unknown"){
						alert("Bentornato ! Il tuo volto è stato riconosciuto");
						window.location.assign("login_conID.php?id="+result+"&");
					}
					else
						alert("Spiacente, volto non riconosciuto. Prova ancora");
				}
            }
        </script>
    </body>
</html>