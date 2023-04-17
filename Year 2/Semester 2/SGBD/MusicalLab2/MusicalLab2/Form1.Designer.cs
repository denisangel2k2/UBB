namespace MusicalLab2
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            parentGridView = new DataGridView();
            childGridView = new DataGridView();
            deleteButton = new Button();
            addButton = new Button();
            refreshButton = new Button();
            label1 = new Label();
            label2 = new Label();
            ((System.ComponentModel.ISupportInitialize)parentGridView).BeginInit();
            ((System.ComponentModel.ISupportInitialize)childGridView).BeginInit();
            SuspendLayout();
            // 
            // parentProdCoardeGridView
            // 
            parentGridView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            parentGridView.Location = new Point(18, 52);
            parentGridView.Margin = new Padding(2);
            parentGridView.Name = "parentProdCoardeGridView";
            parentGridView.RowHeadersWidth = 72;
            parentGridView.RowTemplate.Height = 37;
            parentGridView.Size = new Size(496, 226);
            parentGridView.TabIndex = 0;
            // 
            // childCoardeGridView
            // 
            childGridView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            childGridView.Location = new Point(18, 321);
            childGridView.Margin = new Padding(2);
            childGridView.Name = "childCoardeGridView";
            childGridView.RowHeadersWidth = 72;
            childGridView.RowTemplate.Height = 37;
            childGridView.Size = new Size(496, 251);
            childGridView.TabIndex = 1;
            childGridView.CellValueChanged += childCoardeGridView_CellValueChanged;
            // 
            // deleteButton
            // 
            deleteButton.Location = new Point(112, 587);
            deleteButton.Margin = new Padding(2);
            deleteButton.Name = "deleteButton";
            deleteButton.Size = new Size(89, 36);
            deleteButton.TabIndex = 2;
            deleteButton.Text = "Delete";
            deleteButton.UseVisualStyleBackColor = true;
            deleteButton.Click += deleteButton_Click;
            // 
            // addButton
            // 
            addButton.Location = new Point(18, 587);
            addButton.Name = "addButton";
            addButton.Size = new Size(89, 36);
            addButton.TabIndex = 3;
            addButton.Text = "Add";
            addButton.UseVisualStyleBackColor = true;
            addButton.Click += addButton_Click;
            // 
            // refreshButton
            // 
            refreshButton.Location = new Point(439, 587);
            refreshButton.Name = "refreshButton";
            refreshButton.Size = new Size(75, 36);
            refreshButton.TabIndex = 4;
            refreshButton.Text = "Refresh";
            refreshButton.UseVisualStyleBackColor = true;
            refreshButton.Click += refreshButton_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point);
            label1.Location = new Point(176, 19);
            label1.Name = "label1";
            label1.Size = new Size(158, 21);
            label1.TabIndex = 5;
            label1.Text = "Producatori Coarde";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point);
            label2.Location = new Point(234, 290);
            label2.Name = "label2";
            label2.Size = new Size(64, 21);
            label2.TabIndex = 6;
            label2.Text = "Coarde";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(538, 659);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(refreshButton);
            Controls.Add(addButton);
            Controls.Add(deleteButton);
            Controls.Add(childGridView);
            Controls.Add(parentGridView);
            Margin = new Padding(2);
            Name = "Form1";
            Text = "Form1";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)parentGridView).EndInit();
            ((System.ComponentModel.ISupportInitialize)childGridView).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private DataGridView parentGridView;
        private DataGridView childGridView;
        private Button deleteButton;
        private Button addButton;
        private Button refreshButton;
        private Label label1;
        private Label label2;
    }
}