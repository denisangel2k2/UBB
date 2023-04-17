using Microsoft.Data.SqlClient;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
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

        private SqlConnection connection = null;
        private int currentId = 0;

        private readonly string connectionString = ConfigurationManager.AppSettings["connectionString"];
        private readonly List<string> paramsForInsert = new List<string>(ConfigurationManager.AppSettings["paramsForInsert"].Split(','));
        private readonly List<string> paramsForInsertTypes = new List<string>(ConfigurationManager.AppSettings["paramsForInsertTypes"].Split(','));
        private readonly string insertCommand = ConfigurationManager.AppSettings["insertCommand"];
        private int size = Convert.ToInt32(ConfigurationManager.AppSettings["size"]);


        private TextBox[] textBoxes;
        private Label[] labels;
        private CheckBox[] checkBoxes;

        public Form2(int id_prod)
        {
            InitializeComponent();
            this.currentId = id_prod;

            AddTextBoxesForInserts();
        }

        private void AddTextBoxesForInserts()
        {
            textBoxes = new TextBox[size];
            labels = new Label[size];
            checkBoxes = new CheckBox[size];

            flowLayoutPanel1.WrapContents = true;


            for (int i = 1; i < size; i++)
            {
                if (paramsForInsertTypes[i] == "bool")
                {
                    checkBoxes[i] = new CheckBox();
                    textBoxes[i] = null;
                }
                else
                {
                    checkBoxes[i] = null;
                    textBoxes[i] = new TextBox();
                }
                labels[i] = new Label() { Text = paramsForInsert[i].Substring(1) };

            }
            flowLayoutPanel1.FlowDirection = FlowDirection.TopDown;
            for (int i = 1; i < size; i++)
            {

                flowLayoutPanel1.Controls.Add(labels[i]);
                var spaceLabel = new Label();
                spaceLabel.Size = new Size(10, 10);
                flowLayoutPanel1.Controls.Add(spaceLabel);
                //flowLayoutPanel1.FlowDirection = FlowDirection.LeftToRight;
                if (textBoxes[i] == null)
                    flowLayoutPanel1.Controls.Add(checkBoxes[i]);
                else flowLayoutPanel1.Controls.Add(textBoxes[i]);


            }



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
                    SqlCommand sqlCommand = new SqlCommand(insertCommand, connection);

                    sqlCommand.Parameters.AddWithValue(paramsForInsert[0], currentId);
                    for (int i=1; i < size; i++)
                    {
                        if (textBoxes[i] == null) //checkbox
                        {
                            bool value = checkBoxes[i].Checked;
                            sqlCommand.Parameters.AddWithValue(paramsForInsert[i], value);
                        }
                        else //textbox
                        {
                            string value = textBoxes[i].Text;
                            if (value.Length==0)
                            {
                                MessageBox.Show("Complete everything!");
                                break;
                            }
                            sqlCommand.Parameters.AddWithValue(paramsForInsert[i], value);
                        }
                    }
                    sqlCommand.ExecuteNonQuery();
                    statusLabel.ForeColor = Color.Green;
                    statusLabel.Text = "Inserted successfully!";
                    /*
                    int id_material = Convert.ToInt32(id_matTextBox.Text);
                    int vechime = Convert.ToInt32(vechimeTextBox.Text);
                    bool refolosit = refolositCheckBox.Checked;

                    sqlCommand.Parameters.AddWithValue("@id_prod", id_prod);
                    sqlCommand.Parameters.AddWithValue("@id_material", id_material);
                    sqlCommand.Parameters.AddWithValue("@vechime", vechime);
                    sqlCommand.Parameters.AddWithValue("@refolosit", refolosit);

                    sqlCommand.ExecuteNonQuery();
                    
                    */
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                statusLabel.ForeColor = Color.Red;
                statusLabel.Text = "Error!";
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
