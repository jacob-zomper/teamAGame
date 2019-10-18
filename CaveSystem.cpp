#include "CaveSystem.h"

CaveBlock::CaveBlock()
{}


CaveSystem::CaveSystem()
{
    isEnabled = false;
}

std::string CaveBlock::toString()
{
    return std::to_string(enabled);
}

void printMatrix(CaveBlock *mat[CaveSystem::CAVE_SYSTEM_HEIGHT][CaveSystem::CAVE_SYSTEM_WIDTH], std::size_t N, std::size_t M)
{
    std::cout<<"\n Printing Matrix : \n";
    for(int i = 0 ; i < N ; ++i) {
        for(int j = 0 ; j < M; ++j)
            std::cout << mat[i][j]->toString() << " ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

CaveSystem::CaveSystem(int camX, int camY, int SCREEN_WIDTH)
{
    int i, j;
    int offsetX = camX;
    for (i = 0; i < CAVE_SYSTEM_HEIGHT; i++)
        for (j = 0; j < CAVE_SYSTEM_WIDTH; j++)
        {
            CaveBlock *curr_block = new CaveBlock();
            curr_block->CAVE_BLOCK_ABS_X = offsetX + SCREEN_WIDTH + (j * CaveBlock::CAVE_BLOCK_WIDTH);
            curr_block->CAVE_BLOCK_ABS_Y = i * CaveBlock::CAVE_BLOCK_HEIGHT;

            curr_block->CAVE_BLOCK_REL_X = curr_block->CAVE_BLOCK_ABS_X;
            curr_block->CAVE_BLOCK_REL_Y = curr_block->CAVE_BLOCK_ABS_Y;
            if(i == 0) std::cout << "X: " << std::to_string(curr_block->CAVE_BLOCK_REL_X) << " Y: " << std::to_string(curr_block->CAVE_BLOCK_REL_Y) << " OFFSET_X: " << std::to_string(offsetX) << std::endl;

            if (curr_block->CAVE_BLOCK_REL_Y > 500 || curr_block->CAVE_BLOCK_REL_Y < 250)
                curr_block->enabled = 1;
            else
                curr_block->enabled = 0;

            cave_system[i][j] = curr_block;
        }
    //printMatrix(cave_system, CAVE_SYSTEM_HEIGHT, CAVE_SYSTEM_WIDTH);
}

void CaveSystem::moveCaveBlocks(int camX, int camY)
{
    int i, j;
    for (i = 0; i < CAVE_SYSTEM_HEIGHT; i++)
        for (j = 0; j < CAVE_SYSTEM_WIDTH; j++)
        {
            CaveBlock *curr_block = cave_system[i][j];
            curr_block->CAVE_BLOCK_REL_X = curr_block->CAVE_BLOCK_ABS_X - camX;
        }
}

bool checkCollide(int x, int y, int pWidth, int pHeight, int xTwo, int yTwo, int pTwoWidth, int pTwoHeight)
{
    if (x + pWidth < xTwo || x > xTwo + pTwoWidth)
        return false;
    if (y + pHeight < yTwo || y > yTwo + pTwoHeight)
        return false;
    return true;
}

void CaveSystem::checkCollision(Player *p)
{
    int i, j;
    for (i = 0; i < CAVE_SYSTEM_HEIGHT; i++)
        for (j = 0; j < CAVE_SYSTEM_WIDTH; j++)
        {
            // If there's a collision, cancel the player's move
            if (cave_system[i][j]->enabled == 1 && (checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT, cave_system[i][j]->CAVE_BLOCK_REL_X, cave_system[i][j]->CAVE_BLOCK_REL_Y, cave_system[i][j]->CAVE_BLOCK_WIDTH, cave_system[i][j]->CAVE_BLOCK_HEIGHT)))
            {
                p->undoXMove();
                p->undoYMove();
                // If there's still a collision, it's due to the scrolling and they need to be moved left accordingly
                if (checkCollide(p->getPosX(), p->getPosY(), p->PLAYER_WIDTH, p->PLAYER_HEIGHT, cave_system[i][j]->CAVE_BLOCK_REL_X, cave_system[i][j]->CAVE_BLOCK_REL_Y, cave_system[i][j]->CAVE_BLOCK_WIDTH, cave_system[i][j]->CAVE_BLOCK_HEIGHT))
                {
                    p->setPosX(std::max(cave_system[i][j]->CAVE_BLOCK_REL_X - p->PLAYER_WIDTH, 0));
                    p->redoYMove();
                }
            }
        }
}

void CaveSystem::render(int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_Renderer *gRenderer)
{
    int i, j;
    for (i = 0; i < CAVE_SYSTEM_HEIGHT; i++)
        for (j = 0; j < CAVE_SYSTEM_WIDTH; j++)
        {
            CaveBlock *curr_block = CaveSystem::cave_system[i][j];

            if (curr_block->CAVE_BLOCK_REL_X < SCREEN_WIDTH && curr_block->CAVE_BLOCK_REL_Y < SCREEN_HEIGHT && curr_block->enabled == 1)
            {
                SDL_Rect fillRect = {curr_block->CAVE_BLOCK_REL_X, curr_block->CAVE_BLOCK_REL_Y, CaveBlock::CAVE_BLOCK_WIDTH, CaveBlock::CAVE_BLOCK_HEIGHT};
                SDL_SetRenderDrawColor(gRenderer, 0x7F, 0x33, 0x00, 0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect);
            }
        }
}