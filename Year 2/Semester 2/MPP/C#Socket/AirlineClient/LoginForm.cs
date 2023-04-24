using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;

using System.Windows.Forms;
using System.Configuration;

using log4net;


namespace AirlineClient
{
    public partial class LoginForm : Form
    {

        
        
        private AirlineClientController controller;
        public LoginForm(AirlineClientController controller)
        {
            
            InitializeComponent();
            this.controller =controller;
        }

        

        private void Form1_Load(object sender, EventArgs e)
        {

                   
           
        }

        private void loginButton_Click(object sender, EventArgs e)
        {

            if (usernameTextBox.Text.Length <= 0 || passwordTextBox.Text.Length <= 0) return;

            string username=usernameTextBox.Text.ToString();
            string password=passwordTextBox.Text.ToString();
            try
            {
                controller.login(username, password);
                this.Hide();
                var mainForm=new MainForm(controller);
                mainForm.ShowDialog();
                this.Close();
            }
            catch(Exception ex)
            {
                MessageBox.Show("Authentication failed: " + ex.Message);
            }
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }
    }
}
