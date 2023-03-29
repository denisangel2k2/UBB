using Microsoft.Data.SqlClient;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MusicalLab2
{
    public partial class Form2 : Form
    {
        private string connectionString = @"Server=LAPTOP-RI290K7P\SQLEXPRESS;Database=MusicDatabase;
        Integrated Security=true;TrustServerCertificate=true;";

        private SqlConnection connection = null;
        private int id_prod = 0;
        public Form2(int id_prod)
        {
            InitializeComponent();
            this.id_prod = id_prod;
        }


        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void id_matTextBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void insertButton_Click(object sender, EventArgs e)
        {
            try
            {
                using (connection = new SqlConnection(connectionString))
                {
                    connection.Open();
                    SqlCommand sqlCommand = new SqlCommand("INSERT INTO Coarde (id_prod,id_material_coarda,vechime,refolosit) values (@id_prod,@id_material,@vechime,@refolosit)", connection);
                    int id_material = Convert.ToInt32(id_matTextBox.Text);
                    int vechime = Convert.ToInt32(vechimeTextBox.Text);
                    bool refolosit = refolositCheckBox.Checked;

                    sqlCommand.Parameters.AddWithValue("@id_prod", id_prod);
                    sqlCommand.Parameters.AddWithValue("@id_material", id_material);
                    sqlCommand.Parameters.AddWithValue("@vechime", vechime);
                    sqlCommand.Parameters.AddWithValue("@refolosit", refolosit);

                    sqlCommand.ExecuteNonQuery();
                    statusLabel.ForeColor = Color.Green;
                    statusLabel.Text = "Inserted successfully!";

                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                statusLabel.ForeColor = Color.Red;
                statusLabel.Text = "Error!";
            }
        }
    }
}
