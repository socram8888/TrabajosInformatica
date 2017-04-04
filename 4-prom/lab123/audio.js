'use strict';

(function(window) {
	var audio = document.getElementsByTagName("audio")[0];

	audio.addEventListener("loadeddata", function(e) {
		document.getElementById("duration").innerHTML = Math.floor(audio.duration);
		document.getElementById("tiemporestante").innerHTML = Math.floor(audio.duration);
		document.getElementById("cancion").innerHTML = audio.src;
	});

	audio.addEventListener("timeupdate", function(e) {
		document.getElementById("position").innerHTML = Math.floor(audio.currentTime);
		document.getElementById("progress").value = audio.currentTime / audio.duration;
		document.getElementById("tiemporestante").innerHTML = Math.floor(audio.duration - audio.currentTime);
	});
})(window);



