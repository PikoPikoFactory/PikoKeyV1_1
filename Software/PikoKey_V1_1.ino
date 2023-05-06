//---------------------------
//   Piko Key v1.1
//   Sample Program
//   ver 0.3
//   2023/4/29
//   by Synth Senpai
//---------------------------

#include <MIDI.h>
USING_NAMESPACE_MIDI

//*********************************
//Variable

bool sw_state[15] ;
bool note_state[15] ;
byte note_offset = 48 ;
byte channel  = 1;
byte funcno;
int pgno ;
int vol = 63 ;

bool up_sw_state ;
bool dn_sw_state ;
bool fn_sw_state ;
bool up_sw_state_old ;
bool dn_sw_state_old ;
bool fn_sw_state_old ;
bool sw_state_all = true;

// Pins
const byte LED_DN = 2;
const byte LED_UP = 3;
const byte LED_1  = 13;
const byte SW_DN  = 4;
const byte SW_UP  = 5;
const byte SW15   = 6;
const byte SW14   = 7;
const byte SW13   = 8;
const byte SW12   = 9;
const byte SW11   = 10;
const byte SW10   = 11;
const byte SW09   = 12;
const byte SW08   = 21;
const byte SW07   = 20;
const byte SW06   = 19;
const byte SW05   = 18;
const byte SW04   = 17;
const byte SW03   = 16;
const byte SW02   = 15;
const byte SW01   = 14;
byte sw_map[] = { SW01, SW02, SW03, SW04, SW05, SW06, SW07, SW08, SW09, SW10, SW11, SW12, SW13, SW14};
const byte MAXKEY = 14;

//midi
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

//*********************************************
// setup

void setup() {
  pinMode(LED_DN, OUTPUT);
  pinMode(LED_UP, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(SW_UP, INPUT_PULLUP);
  pinMode(SW_DN, INPUT_PULLUP);
  pinMode(SW15, INPUT_PULLUP);

  for ( byte i = 0 ; i < MAXKEY; i++ )
  {
    pinMode(sw_map[i], INPUT_PULLUP);
  }

  //midi
  MIDI.begin();
  //Start up Animation
  digitalWrite(LED_DN, HIGH);
  delay(200);
  digitalWrite(LED_UP, HIGH);
  delay(200);
  digitalWrite(LED_1, HIGH);
  delay(200);
  digitalWrite(LED_DN, LOW);
  delay(200);
  digitalWrite(LED_UP, LOW);
  delay(200);
  digitalWrite(LED_1, LOW);

  for ( byte i = 0 ; i < MAXKEY; i++ )
  {
    note_state[i] == true;
  }

  // for debug
  // Serial.begin(115200);
  // Serial.println("setup done");

}
// Setup end
//*********************************************

//*********************************************
// Main

void loop() {

  //
  // Key scan
  //
  for ( byte i = 0 ; i < MAXKEY; i++ )
  {
    sw_state[i] =   digitalRead(sw_map[i]);
    if (sw_state[i] == false)
    {
      if (note_state[i] == true)
      {
        note_on(i);
        note_state[i] = false ;
      }
    }
    else
    {
      if (note_state[i] == false)
      {
        note_off(i);
        note_state[i] = true ;
      }
    }
  }

  //
  //Function(Oct up/down, MIDI ch, Program Change)
  //
  up_sw_state = digitalRead(SW_UP);
  dn_sw_state = digitalRead(SW_DN) ;
  fn_sw_state  = digitalRead(SW15);
  //oct up
  if (up_sw_state == false)
  {
    if (up_sw_state_old == true)
    {
      if (note_offset == 36)
      {
        note_offset = 48 ;
        digitalWrite(LED_DN, LOW);
        digitalWrite(LED_UP, LOW);
      } else if (note_offset == 48)
      {
        note_offset = 60 ;
        digitalWrite(LED_DN, LOW);
        digitalWrite(LED_UP, HIGH);
      }
    }
  }
  //oct down
  if (dn_sw_state == false)
  {
    if (dn_sw_state_old == true)
    {
      if (note_offset == 60)
      {
        note_offset = 48 ;
        digitalWrite(LED_DN, LOW);
        digitalWrite(LED_UP, LOW);
      } else if (note_offset == 48)
      {
        note_offset = 36 ;
        digitalWrite(LED_DN, HIGH);
        digitalWrite(LED_UP, LOW);
      }
    }
  }
  //function
  if (fn_sw_state_old == true)
  {
    if (fn_sw_state == false)
    {
      while (sw_state_all == true )
      {

        for ( byte i = 0 ; i < MAXKEY; i++ )
        {
          sw_state[i] =   digitalRead(sw_map[i]);
          if (sw_state[i] == false)
          {
            funcno = i ;
            sw_state_all = false;
          }
        }
      }
      switch (funcno) {
        case 0:
          pgno = 0;
          MIDI.sendProgramChange (pgno , channel );
          break;
        case 1:
          pgno = 20 ;
          MIDI.sendProgramChange (pgno , channel );
          break;
        case 2:
          channel = 1 ;
          break;
        case 3:
          pgno = 40;
          MIDI.sendProgramChange (pgno , channel );
          break;
        case 4:
          channel = 10;
          break;
        case 5:
          pgno = 60 ;
          MIDI.sendProgramChange (pgno , channel );
          break;
        case 6:
          pgno = 80 ;
          MIDI.sendProgramChange (pgno , channel );
          break;
        case 7:
          channel--;
          if (channel < 1)
          {
            channel = 1;
          }
          break;
        case 8:
          vol = vol - 10;
          if (vol < 0)
          {
            vol = 0;
          }
          MIDI.sendControlChange ( 7  , vol , channel );
          break;
        case 9:
          break;
        case 10:
          vol = vol + 10;
          if (vol > 127)
          {
           vol = 127;
          }
          MIDI.sendControlChange ( 7  , vol , channel );
          break;
        case 11:
          channel++;
          if (channel > 16)
          {
            channel = 16;
          }
          break;
        case 12:
          pgno--;
          if (pgno < 0)
          {
            pgno = 0;
          }
          MIDI.sendProgramChange (pgno , channel );
          break;
        case 13:
          pgno++;
          if (pgno > 127)
          {
            pgno = 127;
          }
          MIDI.sendProgramChange (pgno , channel );
          break;
      }
    }
  }

  sw_state_all = true;
  up_sw_state_old = up_sw_state;
  dn_sw_state_old = dn_sw_state ;
  fn_sw_state_old  = fn_sw_state;
}

//  Main end

//********************************************
//MIDI

void note_on(byte keyno)
{
  digitalWrite(LED_1, HIGH);
  byte velocity  = 127;
  byte note;
  note = keyno + note_offset ;
  MIDI.sendNoteOn(note, velocity, channel);
}

void note_off(byte keyno)
{
  digitalWrite(LED_1, LOW);
  byte velocity  = 0;
  byte note;
  note = keyno + note_offset ;
  MIDI.sendNoteOn(note, velocity, channel);
}
