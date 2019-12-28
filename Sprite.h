typedef struct 
{   
   bool isActive = false;
   int velocity = 1;
   bool direction = true;
   int xPos;
   
} lineSprite;

lineSprite line[6];

typedef struct 
{
bool isActive;
   int velocity;
   bool direction;
   int xPos;
   int yPos;
   int angle;
   
} ballSprite;

ballSprite ball[6];

typedef struct 
{
   bool isActive;
   int velocity;
   bool direction;
   int yPos;
   
} rainSprite;

rainSprite rain[];

// int lineSpriteCounter = 0; //Keeps track of how many sprites have been defined

// void spriteInitBall(void);
// void spriteUpdatePositionBall(ballSprite* pSprite);

// void spriteInitLine(void);
// void spriteUpdatePositionLine(lineSprite* pSprite);