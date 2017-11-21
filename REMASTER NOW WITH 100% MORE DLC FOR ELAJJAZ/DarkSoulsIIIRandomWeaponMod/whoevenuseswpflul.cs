using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Windows;

namespace DarkSoulsIIIRandomWeaponMod
{
    class whoevenuseswpflul
    {
        //not really sure
        public const int PROCESS_VM_READ = 0x10;
        public const int TH32CS_SNAPPROCESS = 0x2;
        public const int MEM_COMMIT = 4096;
        public const int PAGE_READWRITE = 4;
        public const int PROCESS_CREATE_THREAD = (0x2);
        public const int PROCESS_VM_OPERATION = (0x8);
        public const int PROCESS_VM_WRITE = (0x20);
        public const int PROCESS_ALL_ACCESS = 0x1f0fff;

        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, Int64 dwProcessId);

        [DllImport("kernel32.dll")]
        public static extern bool ReadProcessMemory(IntPtr hProcess,
     Int64 lpBaseAddress, byte[] lpBuffer, int dwSize, ref int lpNumberOfBytesRead);

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool WriteProcessMemory(IntPtr hProcess,
     Int64 lpBaseAddress, byte[] lpBuffer, int dwSize, ref int lpNumberOfBytesRead);

        [DllImport("kernel32.dll")]
        private static extern bool CloseHandle(IntPtr hObject);

        [DllImport("user32.dll", EntryPoint = "FindWindow")]
        private static extern int FindWindow(string sClass, string sWindow);



        public static List<string> enableweapons = new List<string>();
        private static Thread fgt;
        private static bool shouldrun = false;
        private static double waittime = 1000;

        private static int Weaponsfcs(List<string> weaponlist)
        {
            if (weaponlist.Count == 0)
            {
                // amazing weapon incoming
                return 2030000;
            }

            bool isbossweapon = false;
            char[] delimiterChars = { ' ' };

            Random rnd = new Random();
            int r = rnd.Next(weaponlist.Count());
            string cur = (string)weaponlist[r].Split(delimiterChars)[0];


            for (int i = 0; i < weaponlists.boss_weaponlist.Count(); i++)
            { // Check all boss weapons, we should really just do 2 seperat lists, but meh, this is easier
                string curwpn = weaponlists.boss_weaponlist[i].Split(delimiterChars)[0];
                if (cur == curwpn) { isbossweapon = true; }
            }

            // Check for errors, used when debugging
/*# ifdef _DEBUG
            for (int i = 0; i < cur.length(); ++i)
            {
                const char* current = &cur[i];
                if (!isNumber(current))
                {
                    std::cout << "Invalid character in (" << cur << ")(" << cur[i] << ")" << std::endl;
                    cur.erase(i, 1);
                }
            }
#endif*/

            int Weapon;
            if (cur.Count() > 0) //if not empty
            {
                Weapon = Convert.ToInt32(cur);

                int UpgradeLvl;
                if (isbossweapon)
                {
                    UpgradeLvl = rnd.Next(0, 5);
                }
                else
                {
                    UpgradeLvl = rnd.Next(0, 10);
                }
                Weapon = Weapon + UpgradeLvl;
            }
            else
            {
                //std::cout << "Invalid position in string (" << RandomWeaponIndex << ")" << std::endl;
                Weapon = 2030000;
            }
            return Weapon;
        }

        static private void Threadingman()
        {
            // THREADING ON THE RUN
            Int64 basea = 0x4740178;
            byte[] RWeapon = new byte[sizeof(Int64)];
            Int64 primaryrightweb_offset1 = 0x10;
            Int64 primaryrightweb_offset2 = 0x330;

            int Weapon;


            int id = -1;
            Process[] processes = Process.GetProcesses();
            Process bg = new Process();
            foreach (var pp in processes)
            {
                //Check if Dark Souls is Open
                if (pp.MainWindowTitle.Equals("DARK SOULS III"))
                {
                    id = pp.Id;
                    bg = pp;
                }
            }
            if (id == -1)
            {
                MainWindow.Fails();
                MessageBox.Show("Failed to find process. Please run with administrative privileges.");
                return;
            }
            
            
            IntPtr hprocess = OpenProcess(PROCESS_ALL_ACCESS, false, id);
            if (hprocess.ToInt64() == 0)
            {
                MainWindow.Fails();
                MessageBox.Show("Failed to attach to process. Please run with administrative privileges.");
                return;
            }

            int bytesRead = 0;
            IntPtr ret = IntPtr.Add(bg.MainModule.BaseAddress, (int)basea);
            //var f = ret;
            IntPtr rf;
            IntPtr sec;
            long wepaon = 0;
            ReadProcessMemory(hprocess, ret.ToInt64(), RWeapon, RWeapon.Length, ref bytesRead);
            rf = (IntPtr)BitConverter.ToInt64(RWeapon, 0);
            sec = IntPtr.Add(rf, (int)primaryrightweb_offset1);
            ReadProcessMemory(hprocess, sec.ToInt64(), RWeapon, RWeapon.Length, ref bytesRead);
            rf = (IntPtr)BitConverter.ToInt64(RWeapon, 0);

            sec = IntPtr.Add(rf, (int)primaryrightweb_offset2);
            ReadProcessMemory(hprocess, sec.ToInt64(), RWeapon, RWeapon.Length, ref bytesRead);
            wepaon = BitConverter.ToInt32(RWeapon, 0);

            
            while (shouldrun)
            {
                Weapon = Weaponsfcs(enableweapons);

                WriteProcessMemory(hprocess, sec.ToInt64(), BitConverter.GetBytes(Weapon), 4, ref bytesRead);

                Thread.Sleep(Convert.ToInt32(waittime * 1000));
            }
        }

        static private void merge(List<string> toinsert, List<string> tobeinserted)
        {
            for (int i = 0; i < tobeinserted.Count; i++)
            {
                toinsert.Add(tobeinserted[i]);
            }
        }

        static public void Modlist(
            string wait,
            bool? standard,
            bool? bows,
            bool? whips,
            bool? shields,
            // Infusions
            bool? heavy,
            bool? sharp,
            bool? refined,
            bool? simple,
            bool? crystal,
            bool? fire,
            bool? chaos,
            bool? lightning,
            bool? deep,
            bool? dark,
            bool? poison,
            bool? blood,
            bool? raw,
            bool? blessed,
            bool? hollow,
            // SECRET
            bool? secret
            )
        {
            bool l = double.TryParse(wait, out waittime);
            if (l)
            {
                Debug.Print("ok");
                Debug.Print(Convert.ToString(waittime));
            } else {
                Debug.Print("no");
            }
            enableweapons.Clear();

            if (fire == true)
            {
                Debug.Print("lol");
            }

	        if (standard == true) {

                merge(enableweapons, weaponlists.standardweapons);
		        if (heavy == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Heavy);
                }
		        if (sharp == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Sharp);
                }
		        if (refined == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Refined);
		        }
		        if (simple == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Simple);
		        }
		        if (crystal == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Crystal);
		        }
		        if (fire == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Fire);
		        }
		        if (chaos == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Chaos);
		        }
		        if (lightning == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Lightning);
		        }
		        if (deep == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Deep);
		        }
		        if (dark == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Dark);
		        }
		        if (poison == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Poison);
		        }
		        if (blood == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Blood);
		        }
		        if (raw == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Raw);
		        }
		        if (blessed == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Blessed);
		        }
		        if (hollow == true) {

                    merge(enableweapons, weaponlists.StandardWeapon_Hollow);
		        }
	        }
	        if (bows == true) {

                merge(enableweapons, weaponlists.StandardBows);
	        }
	        if (whips == true) {

                merge(enableweapons, weaponlists.StandardWhip);
		        if (heavy == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Heavy);
		        }
		        if (sharp == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Sharp);
		        }
		        if (refined == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Refined);
		        }
		        if (simple == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Simple);
		        }
		        if (crystal == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Crystal);
		        }
		        if (fire == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Fire);
		        }
		        if (chaos == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Chaos);
		        }
		        if (lightning == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Lightning);
		        }
		        if (deep == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Deep);
		        }
		        if (dark == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Dark);
		        }
		        if (poison == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Poison);
		        }
		        if (blood == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Blood);
		        }
		        if (raw == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Raw);
		        }
		        if (blessed == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Blessed);
		        }
		        if (hollow == true) {

                    merge(enableweapons, weaponlists.StandardWhip_Hollow);
		        }
	        }
	        if (shields == true) {

                merge(enableweapons, weaponlists.StandardShields);
		        if (heavy == true) {

                    merge(enableweapons, weaponlists.StandardShields_Heavy);
		        }
		        if (sharp == true) {

                    merge(enableweapons, weaponlists.StandardShields_Sharp);
		        }
		        if (refined == true) {

                    merge(enableweapons, weaponlists.StandardShields_Refined);
		        }
		        if (simple == true) {

                    merge(enableweapons, weaponlists.StandardShields_Simple);
		        }
		        if (crystal == true) {

                    merge(enableweapons, weaponlists.StandardShields_Crystal);
		        }
		        if (fire == true) {

                    merge(enableweapons, weaponlists.StandardShields_Fire);
		        }
		        if (chaos == true) {

                    merge(enableweapons, weaponlists.StandardShields_Chaos);
		        }
		        if (lightning == true) {

                    merge(enableweapons, weaponlists.StandardShields_Lightning);
		        }
		        if (deep == true) {

                    merge(enableweapons, weaponlists.StandardShields_Deep);
		        }
		        if (dark == true) {

                    merge(enableweapons, weaponlists.StandardShields_Dark);
		        }
		        if (poison == true) {

                    merge(enableweapons, weaponlists.StandardShields_Poison);
		        }
		        if (blood == true) {

                    merge(enableweapons, weaponlists.StandardShields_Blood);
		        }
		        if (raw == true) {

                    merge(enableweapons, weaponlists.StandardShields_Raw);
		        }
		        if (blessed == true) {

                    merge(enableweapons, weaponlists.StandardShields_Blessed);
		        }
		        if (hollow == true) {

                    merge(enableweapons, weaponlists.StandardShields_Hollow);
		        }
	        }

	        if (secret == true) {
		        for (int i = 0; i< 4; i++) {

                    merge(enableweapons, weaponlists.StandardShields);

                    merge(enableweapons, weaponlists.StandardShields_Heavy);

                    merge(enableweapons, weaponlists.StandardShields_Sharp);

                    merge(enableweapons, weaponlists.StandardShields_Refined);

                    merge(enableweapons, weaponlists.StandardShields_Simple);

                    merge(enableweapons, weaponlists.StandardShields_Crystal);

                    merge(enableweapons, weaponlists.StandardShields_Fire);

                    merge(enableweapons, weaponlists.StandardShields_Chaos);

                    merge(enableweapons, weaponlists.StandardShields_Lightning);

                    merge(enableweapons, weaponlists.StandardShields_Deep);

                    merge(enableweapons, weaponlists.StandardShields_Dark);

                    merge(enableweapons, weaponlists.StandardShields_Poison);

                    merge(enableweapons, weaponlists.StandardShields_Blood);

                    merge(enableweapons, weaponlists.StandardShields_Raw);

                    merge(enableweapons, weaponlists.StandardShields_Blessed);

                    merge(enableweapons, weaponlists.StandardShields_Hollow);
		        }
	        }
        }

        static public bool Run()
        {
            if (shouldrun == true) {
                // Stop
                shouldrun = false;
                Thread.Sleep(10);
                fgt.Abort();
            } else {
                // Start
                shouldrun = true;
                fgt = new Thread(Threadingman);
                fgt.Start();
            }
            return shouldrun;
        }

        static public void Stop()
        {
            shouldrun = false;
        }
    }
}
