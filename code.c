#include <dos.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <alloc.h>

void mainMenu();
void game();
void infoScreen();
void clearFrameBuffer();
void gameOver();
void computeCollisions();
void drawPipe();
void setGlobalTextColor();

int posX, posY;
int velocity;
float gravity;
int pipeX1, dt, score, bufferIndex;
char key;
unsigned long ltime, ntime, ticks;
unsigned char far* frameBuffers[4];
char number[3];

int i, j;


const int logo[] = {
    0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,0,0,1,1,0,1,0,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,1,0,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};


void clearFrameBuffer() {
    for (i = 0; i < 4; i++) {
        farfree(frameBuffers[i]);
    }
}

void setVideoMode() {
    union REGS regs;
    regs.h.ah = 0x00;
    regs.h.al = 0x13;
    int86(0x10, &regs, &regs);
}

void setTextMode() {
    union REGS regs;
    clearFrameBuffer();
    regs.h.ah = 0x00;
    regs.h.al = 0x03;
    int86(0x10, &regs, &regs);
    printf("Thank you for playing!\n");
}

void initializeFrameBuffers() {
    for (i = 0; i < 4; i++) {
        frameBuffers[i] = (unsigned char far*)farmalloc(320 * 50);
        if (!frameBuffers[i]) {
            printf("Error: Memory allocation failed!\n");
            exit(1);
        }
    }
}

void drawFrameToScreen() {
    unsigned char far* videoMemory = (unsigned char far*)0xA0000000L;
    for (i = 0; i < 4; i++) {
        movedata(FP_SEG(frameBuffers[i]), FP_OFF(frameBuffers[i]),
                 FP_SEG(videoMemory), FP_OFF(videoMemory + (320 * 50 * i)), 320 * 50);
    }
}

void putPixel(int x, int y, unsigned char color) {
    if (x >= 0 && x < 320 && y >= 0 && y < 200) {
        bufferIndex = y / 50;
        frameBuffers[bufferIndex][(y % 50) * 320 + x] = color;
    }
}

void drawImage(int img[], int width, int height, int posX, int posY, int color, int invert) {
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if(img[i * width + j] == 0x01 && !invert)
            {
                putPixel(j + posX, i + posY, color);
            }
            else if(img[i * width + j] == 0 && invert)
            {
                putPixel(j + posX, i + posY, color);
            }
        }
    }
}


void drawBRect(int px, int py, int sx, int sy, unsigned char col) {
    for (i = 0; i < sx; i++) {
        for (j = 0; j < sy; j++) {
            putPixel(px + i, py + j, col);
        }
    }
}

unsigned long getTicks() {
    union REGS regs;
    regs.h.ah = 0x00;
    int86(0x1A, &regs, &regs);
    ticks = ((unsigned long)regs.x.cx << 16) | regs.x.dx;
    return ticks * 55;
}

void customDelay(unsigned int milliseconds) {
    unsigned long startTicks, currentTicks;
    unsigned long ticksToWait = milliseconds / 55;
    union REGS regs;
    regs.h.ah = 0x00;
    int86(0x1A, &regs, &regs);
    startTicks = regs.x.dx;
    do {
        regs.h.ah = 0x00;
        int86(0x1A, &regs, &regs);
        currentTicks = regs.x.dx;
    } while ((currentTicks - startTicks) < ticksToWait);
}

void computeCollisions(int posX) {
    if (velocity + 25 > 130 && 25 > posX && 25 < posX + 25) {
        gameOver();
    }
    if (velocity + 25 > 130 && 0 > posX && 0 < posX + 25) {
        gameOver();
    }
    if (velocity < 73 && 25 > posX && 25 < posX + 25) {
        gameOver();
    }
    if (velocity < 73 && 0 > posX && 0 < posX + 25) {
        gameOver();
    }
}

void gameOver() {
    printf("\033[H");
    drawBRect(0, 0, 320, 200, 25);
    drawFrameToScreen();
    printf("Game over!\n");
    printf("Your score: ");
    itoa(score, number, 10);
    printf(number);
    printf("\n");
    sleep(1);
    printf("\n");
    printf("Let's try it again!\n");
    printf("\n");
    printf("Press any key to get to menu...\n");
    printf("Press R to restart game...\n");
    key = getch();
    if (key == 'R' || key == 'r') {
        game();
    } else {
        mainMenu();
    }
}

void infoScreen() {
    printf("\033[H");
    drawBRect(0, 0, 320, 200, 3);
    drawFrameToScreen();
    printf("Info:\n");
    printf("\n");
    printf("Press Q to quit this info screen\n");
    printf("\n");
    printf("Created by Simon Smorada in 2024\n");
    printf("This is just an experiment of making a \n game for MS-DOS\n");
    printf("\n");
    printf("Controls:\n");
    printf("E - quit to main menu\n");
    printf("F - Jump\n");
    while (1) {
        key = getch();
        if (key == 'Q' || key == 'q') {
            mainMenu();
        }
    }
}

void drawPipe(int posX, int speed) {
    drawBRect(posX, 130, speed, 25, 48);
    drawBRect(posX + 10, 155, speed, 55, 48);
    drawBRect(posX + 50, 130, speed, 25, 53);
    drawBRect(posX + 10 + 30, 155, speed, 55, 53);

    drawBRect(posX, 50, speed, 25, 48);
    drawBRect(posX + 10, 8, speed, 42, 48);
    drawBRect(posX + 50, 50, speed, 25, 53);
    drawBRect(posX + 10 + 30, 8, speed, 42, 53);
}

void game() {
    gravity = 1;
    velocity = 200 / 2 - 25 /2;
    pipeX1 = 320;
    score = 0;
    drawBRect(0, 8, 320, 192, 53);
    drawFrameToScreen();
    while (1) {
        ltime = getTicks();
        gravity += 0.6;
        velocity += gravity;
        if (gravity >= 10) {
            gravity = 10;
        }
        if (velocity + 25 > 200) {
            gameOver();
        }
        if (velocity < 0) {
            velocity = 0;
        }
        posY += velocity;
        if (kbhit()) {
            key = getch();
            if (key == 'E' || key == 'e') {
                mainMenu();
            }
            if (key == 'W' || key == 'w') {
                posY--;
            } else if (key == 'S' || key == 's') {
                posY++;
            }
            if (key == 'A' || key == 'a') {
                posX--;
            } else if (key == 'D' || key == 'd') {
                posX++;
            }
            if (key == 'F' || key == 'f') {
                gravity = -6;
            }
        }
        if (gravity == 0) {
            drawBRect(posX, velocity, 25, gravity + 1, 53);
            drawBRect(posX, velocity + 25, 25, gravity + 1, 45);
        }
        if (gravity > 0) {
            drawBRect(posX, velocity, 25, gravity + 1, 53);
            drawBRect(posX, velocity + 25, 25, gravity + 1, 45);
        }
        if (gravity < 0) {
            drawBRect(posX, velocity, 25, -gravity + 1, 45);
            drawBRect(posX, velocity + 25, 25, -gravity + 1, 53);
        }
        pipeX1 -= 5;
        if (pipeX1 < -60) {
            pipeX1 = 320;
            score++;
        }
        computeCollisions(pipeX1);
        drawPipe(pipeX1, 5);
        drawFrameToScreen();
        printf("\033[H");
        itoa(score, number, 10);
        printf("                          score: ");
        printf(number);
        ntime = getTicks();
        dt = ntime - ltime;
        if (40 - dt > 0) {
            customDelay(40 - dt);
        }
    }
}

void mainMenu() {
    printf("\033[H");
    drawBRect(0, 0, 320, 200, 11);
    drawImage(logo, 58, 47, 7, 7, 1, 1);

    drawBRect(25, 70, 25, 25, 14);

    drawBRect(120, 42, 50, 25, 48);
    drawBRect(130, 0, 30, 42, 48);

    drawBRect(210, 42, 50, 25, 48);
    drawBRect(220, 0, 30, 42, 48);

    drawFrameToScreen();
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("Press any key to start the game\n");
    printf("Press Q to quit the game\n");
    printf("Press I to see info\n");
    printf("(C) Simon Smorada 2025\n");
    key = getch();
    if (key == 'Q' || key == 'q') {
        setTextMode();
        exit(0);
    } else if (key == 'I' || key == 'i') {
        infoScreen();
    } else {
        drawBRect(0, 0, 320, 8, 0);
        printf("                          score: ");
        game();
    }
}

int main() {
    srand(time(0));
    setVideoMode();
    printf("Loading...");
    initializeFrameBuffers();
    customDelay(3000);
    mainMenu();
    setTextMode();
    return 0;
}
