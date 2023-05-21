using Microsoft.Data.SqlClient;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Deadlock
{
    public partial class Form1 : Form
    {

        private string connectionString = "Server=LAPTOP-RI290K7P\\SQLEXPRESS;Database=MusicDatabase;Integrated Security=true;TrustServerCertificate=true;";
        
        public Form1()
        {
            InitializeComponent();
        }

        private void deadlockBtn_Click(object sender, EventArgs e)
        {
            ThreadStart deadlock1=new ThreadStart(Deadlock1);
            ThreadStart deadlock2 = new ThreadStart(Deadlock2);
            Thread thread1 = new Thread(deadlock1);
            Thread thread2 = new Thread(deadlock2);
            thread1.Start();
            thread2.Start();


        }
        private void Deadlock1()
        {
            Deadlock("deadlock1");
        }
        private void Deadlock2()
        {
            Deadlock("deadlock2");
        }
        private void Deadlock(string procedureName)
        {
            SqlConnection connection=new SqlConnection(connectionString);
            MessageBox.Show(procedureName + " started!");
            SqlCommand cmd = new SqlCommand(procedureName, connection);
            cmd.CommandType = CommandType.StoredProcedure;
            connection.Open();
            int rows_affected = 0;
            try
            {
                rows_affected = cmd.ExecuteNonQuery();
                MessageBox.Show(procedureName + " finished, rows affected: " + rows_affected);
                connection.Close();
            }
            catch(SqlException ex)
            {
                MessageBox.Show(procedureName + " failed!\nRetrying...\n");
                int tries = 3;
                while (rows_affected<2 && tries > 0)
                {
                    MessageBox.Show(procedureName + " failed! rows affected: " + rows_affected + " tries: " + tries);
                    try
                    {
                        rows_affected = cmd.ExecuteNonQuery();
                        MessageBox.Show(procedureName + " finished, rows affected: "+rows_affected+" and "+tries+" tries remaining");
                        connection.Close();
                        tries = 0;
                    }
                    catch (SqlException e)
                    {
                        if (e.Number != 1205)
                        {
                            MessageBox.Show("Transaction has failed!");
                            break;
                        }
                        tries--;
                        MessageBox.Show(procedureName + " failed, " + tries + " remaining");

                    }
                }

            }
        }
    }
}