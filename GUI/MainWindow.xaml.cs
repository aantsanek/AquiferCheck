using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace GUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        [DllImport("AquiferD.dll")]
        public static extern int doNothing(string input);
        //public static extern int doNothing(string input);
        [DllImport("AquiferD.dll")]
        public static extern void calculateButtonClicked(string dataPath, string folderPath);


        public MainWindow()
        {
            InitializeComponent();

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
           
            dlg.DefaultExt = ".DATA";
            dlg.Filter = "DATA Files (*.DATA)|*.DATA";//|*.jpeg|PNG Files (*.png)|*.png|JPG Files (*.jpg)|*.jpg|GIF Files (*.gif)|*.gif";
            Nullable<bool> result = dlg.ShowDialog();
            if (result == true)
            {
                string filename = dlg.FileName;
                dataFilePath.Text = filename;
            }
            Debug.WriteLine("Initialize");
            var t = dataFilePath.Text;
            //int x = doNothing(t);
            //MessageBox.Show(x.ToString());

        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            string dataPath = dataFilePath.Text;
            if (dataPath == "")
            {
                MessageBox.Show("Select a DATA File");
                return;
            }
            string folder = System.IO.Path.GetDirectoryName(dataPath);

            calculateButtonClicked(dataPath, folder);
        }
    }
}
