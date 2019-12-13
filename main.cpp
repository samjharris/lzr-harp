#include "mbed.h"
#include "snd_wave_generator/SoundWaveGenerator.h"
#include "snd_wave_generator/TriangleWave.h"
#include "snd_wave_generator/SineWave.h"
#include "snd_wave_generator/WaveCombo.h"
#include <math.h>

using namespace snd_wave_generator;

AnalogOut DAC_pin(p18); //DAC pin
SoundWaveGenerator g(16000); //Sound generator object

//Pins mapped to "beams".
//beam0 is the lowest beam,
//beam4 is the highest
DigitalIn beam0(p25);
DigitalIn beam1(p21);
DigitalIn beam2(p22);
DigitalIn beam3(p23);
DigitalIn beam4(p24);

// code to code number
int code2int(char c){
  int ret = -1;
  switch(c){
  case 'C': ret = 0; break;
  case 'c': ret = 1; break; // C#/Db
  case 'D': ret = 2; break;
  case 'd': ret = 3; break; // D#/Eb
  case 'E': ret = 4; break;
  case 'F': ret = 5; break;
  case 'f': ret = 6; break; // F#/Gb
  case 'G': ret = 7; break;
  case 'g': ret = 8; break; // G#/Ab
  case 'A': ret = 9; break;
  case 'a': ret = 10; break; // A#/Bb
  case 'B': ret = 11; break;
  default:
    ret = -1;
  }
  //printf("case%d\r\n",ret);
  return ret;
}
 
// (C, C#, D, D#, E, F, F#, G, G#, A, A#, B)
float w(int ov,char code) {
  int note_no = code2int(code) + (ov + 2) * 12;
  return 440 * pow(2.0 , (note_no - 69) / 12.0 );
}

SineWave note_C3(w(3,'C'));SineWave note_C4(w(4,'C'));SineWave note_C5(w(5,'C'));
SineWave note_c3(w(3,'c'));SineWave note_c4(w(4,'c'));SineWave note_c5(w(5,'c'));
SineWave note_D3(w(3,'D'));SineWave note_D4(w(4,'D'));SineWave note_D5(w(5,'D'));
SineWave note_d3(w(3,'d'));SineWave note_d4(w(4,'d'));SineWave note_d5(w(5,'d'));
SineWave note_E3(w(3,'E'));SineWave note_E4(w(4,'E'));SineWave note_E5(w(5,'E'));
SineWave note_F3(w(3,'F'));SineWave note_F4(w(4,'F'));SineWave note_F5(w(5,'F'));
SineWave note_f3(w(3,'f'));SineWave note_f4(w(4,'f'));SineWave note_f5(w(5,'f'));
SineWave note_G3(w(3,'G'));SineWave note_G4(w(4,'G'));SineWave note_G5(w(5,'G'));
SineWave note_g3(w(3,'g'));SineWave note_g4(w(4,'g'));SineWave note_g5(w(5,'g'));
SineWave note_A3(w(3,'A'));SineWave note_A4(w(4,'A'));SineWave note_A5(w(5,'A'));
SineWave note_a3(w(3,'a'));SineWave note_a4(w(4,'a'));SineWave note_a5(w(5,'a'));
SineWave note_B3(w(3,'B'));SineWave note_B4(w(4,'B'));SineWave note_B5(w(5,'B'));

// play with length
void p(SineWave *s,float length){
  g.play(s);wait(length);
}
// stop length
void s(float stop){
  g.stop();wait(stop);
}
 
// defines of sound sequenses
void jingle(void){
  p(&note_E3,0.2);
  p(&note_E3,0.2);
  p(&note_E3,0.2);
  p(&note_B3,0.2);
  p(&note_D3,0.2);
  p(&note_D3,0.2);
  p(&note_D3,0.2);
  p(&note_B3,0.2);
  p(&note_E3,0.2);
  p(&note_E3,0.2);
  p(&note_E3,0.2);
  p(&note_B3,0.2);
  p(&note_C3,0.2);
  s(0.2);
  
}

int main() {
    //Set the beam pins' modes
    beam0.mode(PullDown);
    beam1.mode(PullDown);
    beam2.mode(PullDown);
    beam3.mode(PullDown);
    beam4.mode(PullDown);
    
    //Organize the beam pins
    //DigitalIn *beams[] = {&beam0,&beam1,&beam2,&beam3,&beam4};
    DigitalIn *beams[] = {&beam4,&beam3,&beam2,&beam1,&beam0};
    
    //All of our notes: 
    //Normal scale:   
    /*
    SineWave *notes[] = {
            &note_C3, &note_C3, &note_c3, &note_D3, &note_d3, &note_E3, &note_F3, 
            &note_f3, &note_G3, &note_g3, &note_A3, &note_a3, &note_B3, &note_C4, 
            &note_c4, &note_D4, &note_d4, &note_E4, &note_F4, &note_f4, &note_G4, 
            &note_g4, &note_A4, &note_a4, &note_B4, &note_C5, &note_c5, &note_D5, 
            &note_d5, &note_E5, &note_f5
        };
    */
    //Piano w/o semitones, wrapping octave 3,4:
    
    SineWave *notes[] = {
            &note_C3, &note_D3, &note_E3, &note_F3, &note_G3, &note_A3, &note_B3, 
            &note_C4, &note_D4, &note_E4, &note_F4, &note_G4, &note_A4, &note_B4, &note_C3, 
            &note_D3, &note_E3, &note_F3, &note_G3, &note_A3, &note_B3, &note_C4, &note_D4, 
            &note_E4, &note_F4, &note_G4,&note_A4, &note_B4, &note_C3, &note_D3, &note_E3
        };
    
    //Play a little tune first...
    jingle();
    
    //Wait-time (Seconds to play each note)
    #define WAITTM 0.35;

    //Store the previous state of the
    short prev = 0;
    while(1){
        //read the beams
        short cur = 0;
        for(int i = 0; i < 5; i++){
            short b = beams[i]->read();
            if(!b){    
                cur += (int) pow(2.0,i);
            }else if(b){
            }   
        }
        
        short play = 0;
        if(cur != prev){
            play = cur;
        }
        prev = cur;
        
        //play some music! (hash into the note array to get the note to play)
        SineWave *note = notes[play-1];
        
        float wait = WAITTM;
        if(!play){
            s(0.1);   
        }else{
            p(note,wait);
        }
           
    }
    
}
