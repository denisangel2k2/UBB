namespace AirlineClient
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.filteredFlightsGridView = new System.Windows.Forms.DataGridView();
            this.allFlightsGridView = new System.Windows.Forms.DataGridView();
            this.loggedUserLabel = new System.Windows.Forms.Label();
            this.destinationTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.searchButton = new System.Windows.Forms.Button();
            this.logoutButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.filteredFlightsGridView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.allFlightsGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // filteredFlightsGridView
            // 
            this.filteredFlightsGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.filteredFlightsGridView.Location = new System.Drawing.Point(191, 63);
            this.filteredFlightsGridView.Name = "filteredFlightsGridView";
            this.filteredFlightsGridView.Size = new System.Drawing.Size(453, 150);
            this.filteredFlightsGridView.TabIndex = 0;
            this.filteredFlightsGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.filteredFlightsGridView_CellFormatting);
            this.filteredFlightsGridView.Click += new System.EventHandler(this.filteredFlightsGridView_Click);
            // 
            // allFlightsGridView
            // 
            this.allFlightsGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.allFlightsGridView.Location = new System.Drawing.Point(191, 258);
            this.allFlightsGridView.Name = "allFlightsGridView";
            this.allFlightsGridView.Size = new System.Drawing.Size(453, 150);
            this.allFlightsGridView.TabIndex = 1;
            this.allFlightsGridView.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler(this.allFlightsGridView_CellFormatting);
            // 
            // loggedUserLabel
            // 
            this.loggedUserLabel.AutoSize = true;
            this.loggedUserLabel.Location = new System.Drawing.Point(29, 28);
            this.loggedUserLabel.Name = "loggedUserLabel";
            this.loggedUserLabel.Size = new System.Drawing.Size(35, 13);
            this.loggedUserLabel.TabIndex = 2;
            this.loggedUserLabel.Text = "label1";
            // 
            // destinationTextBox
            // 
            this.destinationTextBox.Location = new System.Drawing.Point(254, 37);
            this.destinationTextBox.Name = "destinationTextBox";
            this.destinationTextBox.Size = new System.Drawing.Size(156, 20);
            this.destinationTextBox.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(188, 43);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Destination";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(416, 40);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(30, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "Date";
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.Location = new System.Drawing.Point(457, 37);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(187, 20);
            this.dateTimePicker1.TabIndex = 7;
            // 
            // searchButton
            // 
            this.searchButton.Location = new System.Drawing.Point(569, 219);
            this.searchButton.Name = "searchButton";
            this.searchButton.Size = new System.Drawing.Size(75, 23);
            this.searchButton.TabIndex = 8;
            this.searchButton.Text = "Search";
            this.searchButton.UseVisualStyleBackColor = true;
            this.searchButton.Click += new System.EventHandler(this.searchButton_Click);
            // 
            // logoutButton
            // 
            this.logoutButton.Location = new System.Drawing.Point(12, 415);
            this.logoutButton.Name = "logoutButton";
            this.logoutButton.Size = new System.Drawing.Size(75, 23);
            this.logoutButton.TabIndex = 9;
            this.logoutButton.Text = "Logout";
            this.logoutButton.UseVisualStyleBackColor = true;
            this.logoutButton.Click += new System.EventHandler(this.logoutButton_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(700, 450);
            this.Controls.Add(this.logoutButton);
            this.Controls.Add(this.searchButton);
            this.Controls.Add(this.dateTimePicker1);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.destinationTextBox);
            this.Controls.Add(this.loggedUserLabel);
            this.Controls.Add(this.allFlightsGridView);
            this.Controls.Add(this.filteredFlightsGridView);
            this.Name = "MainForm";
            this.Text = "Form2";
            this.Load += new System.EventHandler(this.Form2_Load);
            ((System.ComponentModel.ISupportInitialize)(this.filteredFlightsGridView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.allFlightsGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView filteredFlightsGridView;
        private System.Windows.Forms.DataGridView allFlightsGridView;
        private System.Windows.Forms.Label loggedUserLabel;
        private System.Windows.Forms.TextBox destinationTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
        private System.Windows.Forms.Button searchButton;
        private System.Windows.Forms.Button logoutButton;
    }
}