typedef struct 
{   
   bool isActive = false;
   int velocity = 1;
   bool direction = true;
   int xPos;
   
} lineSprite;

lineSprite qline[6];

typedef struct 
{
bool isActive;
   int velocity;
   bool direction;
   int xPos;
   int yPos;
   int angle;
   
} ballSprite;

ballSprite qball[6];



// int lineSpriteCounter = 0; //Keeps track of how many sprites have been defined

// void spriteInitBall(void);
// void spriteUpdatePositionBall(ballSprite* pSprite);

// void spriteInitLine(void);
// void spriteUpdatePositionLine(lineSprite* pSprite);
