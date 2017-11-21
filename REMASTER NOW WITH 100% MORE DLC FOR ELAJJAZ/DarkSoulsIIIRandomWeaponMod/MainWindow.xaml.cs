using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace DarkSoulsIIIRandomWeaponMod
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

    public MainWindow()
        {
            InitializeComponent();
        }

        // Not stolen from pro website https://stackoverflow.com/questions/11377977/global-hotkeys-in-wpf-working-from-every-window
        [DllImport("User32.dll")]
        private static extern bool RegisterHotKey(
            [In] IntPtr hWnd,
            [In] int id,
            [In] uint fsModifiers,
            [In] uint vk);

        [DllImport("User32.dll")]
        private static extern bool UnregisterHotKey(
            [In] IntPtr hWnd,
            [In] int id);

        private HwndSource _source;
        private const int HOTKEY_ID = 9000;

        protected override void OnSourceInitialized(EventArgs e)
        {
            base.OnSourceInitialized(e);
            var helper = new WindowInteropHelper(this);
            _source = HwndSource.FromHwnd(helper.Handle);
            _source.AddHook(HwndHook);
            RegisterHotKey();
        }

        protected override void OnClosed(EventArgs e)
        {
            _source.RemoveHook(HwndHook);
            _source = null;
            UnregisterHotKey();
            base.OnClosed(e);
        }

        private void RegisterHotKey()
        {
            var helper = new WindowInteropHelper(this);
            const uint KEY_X = 0x58;
            const uint MOD_ALT = 0x0001;
            if (!RegisterHotKey(helper.Handle, HOTKEY_ID, MOD_ALT, KEY_X))
            {
                // handle error
            }
        }

        private void UnregisterHotKey()
        {
            var helper = new WindowInteropHelper(this);
            UnregisterHotKey(helper.Handle, HOTKEY_ID);
        }

        private IntPtr HwndHook(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            const int WM_HOTKEY = 0x0312;
            switch (msg)
            {
                case WM_HOTKEY:
                    switch (wParam.ToInt32())
                    {
                        case HOTKEY_ID:
                            OnHotKeyPressed();
                            handled = true;
                            break;
                    }
                    break;
            }
            return IntPtr.Zero;
        }

        private void handlemicri()
        {
            if (whoevenuseswpflul.Run())
            {
                // Running
                Start.Content = "Stop";
            }
            else
            {
                // Not running
                Start.Content = "Start";
            }
        }

        private void OnHotKeyPressed()
        {
            handlemicri();
        }

        private void Start_Click(object sender, RoutedEventArgs e)
        {
            handlemicri();
        }

        static public void Fails()
        {
            // Not running
            ((MainWindow)Application.Current.MainWindow).Start.Content = "Start";
        }

        private void sendupdate()
        {
            // Best way to make program, put shit code elsewhere
            whoevenuseswpflul.Modlist(timer.Text, StandWeap.IsChecked, Bows.IsChecked, Whips.IsChecked, Shields.IsChecked, Heavy_infusions.IsChecked, Sharp_infusions.IsChecked, Refined_infusions.IsChecked, Simple_infusions.IsChecked, Crystal_infusions.IsChecked, Fire_infusions.IsChecked, Chaos_infusions.IsChecked, Lightning_infusions.IsChecked, Deep_infusions.IsChecked, Dark_infusions.IsChecked, Poison_infusions.IsChecked, Blood_infusions.IsChecked, Raw_infusions.IsChecked, Blessed_infusions.IsChecked, Hollow_infusions.IsChecked, Secret.IsChecked);
        }

        private void StandWeap_Checked(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void Bows_Checked(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void Shields_Checked(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_1(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_2(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_3(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_4(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_5(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_6(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_7(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_8(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_9(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_10(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_11(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_12(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_13(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_14(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_15(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void ListBoxItem_Selected_16(object sender, RoutedEventArgs e)
        {
            sendupdate();
        }

        private void Closingg(object sender, System.ComponentModel.CancelEventArgs e)
        {
            whoevenuseswpflul.Stop();
        }

        private void timer_TextChanged(object sender, TextChangedEventArgs e)
        {
            sendupdate();
        }

        private void Secret_Checked(object sender, RoutedEventArgs e)
        {
            sendupdate();
            Secret.Content = "Znorq: only thing i find about 'secret' option is 'shouto out to Elajjaz for trying the mod and testing the secret option' so no help there : )";
        }
        
        int k = 0;
        private void testt(object sender, MouseButtonEventArgs e)
        {
            k += 1;
            if (k >= 20)
            {
                Status.Content = "Usable: U bored?";
            }
        }
    }
}
