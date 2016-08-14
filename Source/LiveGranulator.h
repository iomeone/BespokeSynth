//
//  LiveGranulator.h
//  modularSynth
//
//  Created by Ryan Challinor on 10/2/13.
//
//

#ifndef __modularSynth__LiveGranulator__
#define __modularSynth__LiveGranulator__

#include <iostream>
#include "IAudioProcessor.h"
#include "IDrawableModule.h"
#include "Checkbox.h"
#include "Granulator.h"
#include "Slider.h"
#include "RollingBuffer.h"
#include "Transport.h"
#include "DropdownList.h"

#define FREEZE_EXTRA_SAMPLES_COUNT 2*gSampleRate

class LiveGranulator : public IAudioProcessor, public IFloatSliderListener, public ITimeListener, public IDropdownListener
{
public:
   LiveGranulator();
   virtual ~LiveGranulator();
   
   static IAudioProcessor* Create() { return new LiveGranulator(); }
   
   string GetTitleLabel() override { return "granulator"; }
   void CreateUIControls() override;
   
   //IAudioProcessor
   void ProcessAudio(double time, float* audio, int bufferSize) override;
   void SetEnabled(bool enabled) override { mEnabled = enabled; }
   float GetEffectAmount() override;
   string GetType() override { return "granulator"; }
   
   void OnTimeEvent(int samplesIn) override;
   
   void CheckboxUpdated(Checkbox* checkbox) override;
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override;
   void DropdownUpdated(DropdownList* list, int oldVal) override;
   
private:
   void Freeze();
   
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(int& w, int& h) override;
   bool Enabled() const override { return mEnabled; }   
   
   float mBufferLength;
   RollingBuffer mBuffer;
   Granulator mGranulator;
   FloatSlider* mGranSpacing;
   FloatSlider* mGranSpeed;
   FloatSlider* mGranLengthMs;
   FloatSlider* mGranPosRandomize;
   FloatSlider* mGranSpeedRandomize;
   FloatSlider* mGranSpacingRandomize;
   Checkbox* mGranOctaveCheckbox;
   bool mAdd;
   Checkbox* mAddCheckbox;
   bool mFreeze;
   Checkbox* mFreezeCheckbox;
   int mFreezeExtraSamples;
   float mPos;
   FloatSlider* mPosSlider;
   float mDCEstimate;   //estimate of DC offset
   NoteInterval mAutoCaptureInterval;
   DropdownList* mAutoCaptureDropdown;
};

#endif /* defined(__modularSynth__LiveGranulator__) */

