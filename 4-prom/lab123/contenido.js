'use strict';

(function(window) {
	var video = document.getElementsByTagName("video")[0];

	video.addEventListener("loadeddata", function(e) {
		document.getElementById("duration").innerHTML = Math.floor(video.duration);
	});

	video.addEventListener("timeupdate", function(e) {
		document.getElementById("position").innerHTML = Math.floor(video.currentTime);
		document.getElementById("progress").value = video.currentTime / video.duration;
	});

	video.addEventListener("play", function() {
		video.classList.add("playing");
	});

	video.addEventListener("pause", function() {
		video.classList.remove("playing");
	});

	video.addEventListener("click", function() {
		if (video.paused) {
			video.play();
		} else {
			video.pause();
		}
	});

	document.getElementById("play").addEventListener("click", function() {
		video.playbackRate = 1;
		video.play();
	});

	document.getElementById("pause").addEventListener("click", function() {
		video.pause();
	});

	document.getElementById("stop").addEventListener("click", function() {
		video.pause();
		video.currentTime = 0;
	});

	document.getElementById("fastforward").addEventListener("click", function() {
		video.playbackRate++;
		video.play();
	});

	document.getElementById("volume").addEventListener("change", function(e) {
		video.volume = e.target.value / 100.0;
	});
})(window);
