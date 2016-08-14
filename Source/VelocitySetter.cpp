//
//  VelocitySetter.cpp
//  modularSynth
//
//  Created by Ryan Challinor on 5/16/13.
//
//

#include "VelocitySetter.h"
#include "OpenFrameworksPort.h"
#include "SynthGlobals.h"
#include "ModularSynth.h"

VelocitySetter::VelocitySetter()
: mVelocity(.65f)
, mVelocitySlider(NULL)
, mRandomness(0)
, mRandomnessSlider(NULL)
{
   SetEnabled(false);
}

void VelocitySetter::CreateUIControls()
{
   IDrawableModule::CreateUIControls();
   mVelocitySlider = new FloatSlider(this,"vel",5,2,80,15,&mVelocity,0,1);
   mRandomnessSlider = new FloatSlider(this,"rand",5,20,80,15,&mRandomness,0,1);
}

void VelocitySetter::DrawModule()
{
   if (Minimized() || IsVisible() == false)
      return;
   
   mVelocitySlider->Draw();
   mRandomnessSlider->Draw();
}

void VelocitySetter::CheckboxUpdated(Checkbox *checkbox)
{
}

void VelocitySetter::PlayNote(double time, int pitch, int velocity, int voiceIdx /*= -1*/, ModulationChain* pitchBend /*= NULL*/, ModulationChain* modWheel /*= NULL*/, ModulationChain* pressure /*= NULL*/)
{
   ComputeSliders(0);
   
   float random = ofRandom(1-mRandomness,1);
   
   if (mEnabled && velocity != 0)
   {
      PlayNoteOutput(time, pitch, int(mVelocity*127*random), voiceIdx, pitchBend, modWheel, pressure);
   }
   else
   {
      PlayNoteOutput(time, pitch, int(velocity*random), voiceIdx, pitchBend, modWheel, pressure);
      if (velocity != 0)
         mVelocity = velocity / 127.0f;
   }
}

void VelocitySetter::LoadLayout(const ofxJSONElement& moduleInfo)
{
   mModuleSaveData.LoadString("target", moduleInfo);

   SetUpFromSaveData();
}

void VelocitySetter::SetUpFromSaveData()
{
   SetUpPatchCables(mModuleSaveData.GetString("target"));
}

