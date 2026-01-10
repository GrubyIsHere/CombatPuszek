#include <A_Robot.h>

//-------------//
// INICJALIZACJE//
//-------------//

// Konstruktor
A_Robot::A_Robot()
{
  battery = new S_Battery();
  buzzer = new S_Buzzer();
  lights = new S_Lights();
  saw = new S_Saw();
  tracks = new S_Tracks();

  Init();
}

//---------------//
// DEFINICJE METOD//
//---------------//

int A_Robot::ManualControl()
{
  //connection lost
  if (!control.connected)
  {
    tracks->Brake(tracks->LEFT);
    tracks->Brake(tracks->RIGHT);
    saw->Stop();
    lights->Off(lights->FRONT_LEFT);
    lights->Off(lights->BACK_LEFT);
    lights->Off(lights->FRONT_RIGHT);
    lights->Off(lights->BACK_RIGHT);
    return 1;
  }

  // panic button
  if (control.brake)
  {
    tracks->Brake(tracks->LEFT);
    tracks->Brake(tracks->RIGHT);

    saw->Stop();
    saw_first_started = 0; //resetujemy, żeby piła z dupy nie wstawała

    lights->On(lights->FRONT_LEFT);
    lights->On(lights->BACK_LEFT);
    lights->On(lights->FRONT_RIGHT);
    lights->On(lights->BACK_RIGHT);
    return 2;
  }

  // saw on/off
  if (control.saw)
  {
    saw->Start();
    saw_first_started = 1; //ustawiamy, żeby kręcił sie na jałowych po starcie walki
  }
  else
  {
    if (saw_first_started)
    {
      saw->Hold();
    }
    else
    {
      saw->Stop();
    }
  }

  // jazda
  if (control.speed_left > 0)
  {
    tracks->Move(tracks->LEFT, tracks->FORWARD, control.speed_left);
    lights->Dim(lights->FRONT_LEFT, control.speed_left);
    lights->Off(lights->BACK_LEFT);
    lights->On(lights->FRONT_LEFT);
  }
  else if (control.speed_left < 0)
  {
    tracks->Move(tracks->LEFT, tracks->BACKWARD, -control.speed_left);
    lights->Dim(lights->BACK_LEFT, -control.speed_left);
    lights->Off(lights->FRONT_LEFT);
    lights->On(lights->BACK_LEFT);
  }
  else
  {
    tracks->Stop(tracks->LEFT);
    lights->Off(lights->FRONT_LEFT);
    lights->Off(lights->BACK_LEFT);
  }

  if (control.speed_right > 0)
  {
    tracks->Move(tracks->RIGHT, tracks->FORWARD, control.speed_right);
    lights->Dim(lights->FRONT_RIGHT, control.speed_right);
    lights->Off(lights->BACK_RIGHT);
    lights->On(lights->FRONT_RIGHT);
  }
  else if (control.speed_right < 0)
  {
    tracks->Move(tracks->RIGHT, tracks->BACKWARD, -control.speed_right);
    lights->Dim(lights->BACK_RIGHT, -control.speed_right);
    lights->Off(lights->FRONT_RIGHT);
    lights->On(lights->BACK_RIGHT);
  }
  else
  {
    tracks->Stop(tracks->RIGHT);
    lights->Off(lights->FRONT_RIGHT);
    lights->Off(lights->BACK_RIGHT);
  }

  return 0;
}

void A_Robot::Init()
{
  lights->Toggle(lights->FRONT_LEFT);
  lights->Toggle(lights->FRONT_RIGHT);
  lights->Toggle(lights->BACK_LEFT);
  lights->Toggle(lights->BACK_RIGHT);

  lights->Blink(lights->FRONT_RIGHT, 3, 7);
  lights->Blink(lights->FRONT_LEFT, 3, 7);
  lights->Blink(lights->BACK_LEFT, 3, 7);
  lights->Blink(lights->BACK_RIGHT, 3, 7);

  // tracks->Stop(tracks->LEFT);
  // tracks->Stop(tracks->RIGHT);

  saw->SetSpeed(100); //WAŻNE!
}

int A_Robot::BatteryCheck()
{
  // overvoltage
  if (battery->ReportError() > 2)
  {
    lights->Blink(lights->FRONT_RIGHT, 1, 3);
    lights->Blink(lights->FRONT_LEFT, 1, 3);
    lights->Blink(lights->BACK_LEFT, 1, 3);
    lights->Blink(lights->BACK_RIGHT, 1, 3);
    buzzer->Waw();
    return 1;
  }

  // undervoltage
  if (battery->ReportError() == 2 || battery->ReportError() == 1)
  {
    lights->Off(lights->BACK_LEFT);
    lights->Off(lights->BACK_RIGHT);
    lights->Off(lights->FRONT_LEFT);
    lights->Off(lights->FRONT_RIGHT);
    buzzer->Waw();
    return 2;
  }

  return 0;
}