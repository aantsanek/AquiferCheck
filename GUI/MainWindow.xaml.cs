using System;
using System.Windows;
using System.Runtime.InteropServices;
using System.Diagnostics;
using Microsoft.Win32;
using System.IO;

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

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            
            saveFileDialog.Filter = "csv files (*.csv)|*.csv";
            saveFileDialog.FilterIndex = 2;
            saveFileDialog.RestoreDirectory = true;
            saveFileDialog.ShowDialog();

            if (saveFileDialog.FileName != "")
            {
                string[] lines = { "Well1,1200", "'Well2',1340", "ThirdWell,980" };
                System.IO.File.WriteAllLines(saveFileDialog.FileName, lines);
            }
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {

        }
    }
}
