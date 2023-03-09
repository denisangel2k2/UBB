using Microsoft.Data.SqlClient;
using System.Data;

namespace Lab1SelectJoburi
{
    public partial class Form1 : Form
    {
        string connection_string = @"Server=LAPTOP-RI290K7P\SQLEXPRESS;Database=Laborator1224-2SGBD2023;
        Integrated Security=true;TrustServerCertificate=true;";
        DataSet dataSet = new DataSet();
        SqlDataAdapter sqlDataAdapter = new SqlDataAdapter();

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                using(SqlConnection connection = new SqlConnection(connection_string))
                {
                    connection.Open();
                    MessageBox.Show(connection.State.ToString());
                    sqlDataAdapter.SelectCommand = new SqlCommand("SELECT * FROM Joburi;",connection);
                    sqlDataAdapter.Fill(dataSet, "Joburi");
                    dataGridView1.DataSource = dataSet.Tables["Joburi"];

                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                using (SqlConnection connection = new SqlConnection(connection_string))
                {
                    sqlDataAdapter.SelectCommand.Connection = connection;
                    sqlDataAdapter.Fill(dataSet, "Joburi");
                    if (dataSet.Tables.Contains("Joburi"))
                        dataSet.Tables["Joburi"]
                            .Clear();
                    sqlDataAdapter.Fill(dataSet, "Joburi");
                    dataGridView1.DataSource = dataSet.Tables["Joburi"];

                }  
            }
            catch(Exception ex) 
            { 
                MessageBox.Show(ex.Message); 
            }

        }
    }
}