#include "InstructionState.h"
#include "../../screens/InstructionScreen.h"

void InstructionState::Init() {
    instructionScreen = new InstructionScreen();
    instructionScreen->Init();
}

void InstructionState::Update() {
    instructionScreen->Update();
}

void InstructionState::Draw() {
    instructionScreen->Draw();
}

void InstructionState::Unload() {
    instructionScreen->Unload();
    delete instructionScreen;
    instructionScreen = nullptr;
}

InstructionState::~InstructionState() {
    delete instructionScreen;
}