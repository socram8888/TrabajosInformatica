
float avg = 0;
float MAX_VEL = 30;
float OLD_WEIGHT = 0.8;

void setup() {
  size(640, 480);
  colorMode(HSB, 100);
  noStroke();
}

void draw() {
  background(0, 0, 0);
  
  float vel = sqrt(pow(pmouseX - mouseX, 2) + pow(pmouseY - mouseY, 2));
  if (vel > MAX_VEL) {
    vel = MAX_VEL;
  }

  // Apply IIR filter
  avg = avg * OLD_WEIGHT + vel * (1 - OLD_WEIGHT) / MAX_VEL;

  fill(avg * 100, 100, 100);
  ellipse(mouseX, mouseY, 20, 20);
}