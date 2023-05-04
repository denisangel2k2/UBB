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
            // parentGridView
            // 
            parentGridView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            parentGridView.Location = new Point(21, 69);
            parentGridView.Margin = new Padding(2, 3, 2, 3);
            parentGridView.Name = "parentGridView";
            parentGridView.RowHeadersWidth = 72;
            parentGridView.RowTemplate.Height = 37;
            parentGridView.Size = new Size(567, 301);
            parentGridView.TabIndex = 0;
            // 
            // childGridView
            // 
            childGridView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            childGridView.Location = new Point(21, 428);
            childGridView.Margin = new Padding(2, 3, 2, 3);
            childGridView.Name = "childGridView";
            childGridView.RowHeadersWidth = 72;
            childGridView.RowTemplate.Height = 37;
            childGridView.Size = new Size(567, 335);
            childGridView.TabIndex = 1;
            childGridView.CellValueChanged += childCoardeGridView_CellValueChanged;
            // 
            // deleteButton
            // 
            deleteButton.Location = new Point(128, 783);
            deleteButton.Margin = new Padding(2, 3, 2, 3);
            deleteButton.Name = "deleteButton";
            deleteButton.Size = new Size(102, 48);
            deleteButton.TabIndex = 2;
            deleteButton.Text = "Delete";
            deleteButton.UseVisualStyleBackColor = true;
            deleteButton.Click += deleteButton_Click;
            // 
            // addButton
            // 
            addButton.Location = new Point(21, 783);
            addButton.Margin = new Padding(3, 4, 3, 4);
            addButton.Name = "addButton";
            addButton.Size = new Size(102, 48);
            addButton.TabIndex = 3;
            addButton.Text = "Add";
            addButton.UseVisualStyleBackColor = true;
            addButton.Click += addButton_Click;
            // 
            // refreshButton
            // 
            refreshButton.Location = new Point(502, 783);
            refreshButton.Margin = new Padding(3, 4, 3, 4);
            refreshButton.Name = "refreshButton";
            refreshButton.Size = new Size(86, 48);
            refreshButton.TabIndex = 4;
            refreshButton.Text = "Refresh";
            refreshButton.UseVisualStyleBackColor = true;
            refreshButton.Click += refreshButton_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point);
            label1.Location = new Point(253, 21);
            label1.Name = "label1";
            label1.Size = new Size(74, 28);
            label1.TabIndex = 5;
            label1.Text = "Parent";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point);
            label2.Location = new Point(267, 387);
            label2.Name = "label2";
            label2.Size = new Size(60, 28);
            label2.TabIndex = 6;
            label2.Text = "Child";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(615, 879);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(refreshButton);
            Controls.Add(addButton);
            Controls.Add(deleteButton);
            Controls.Add(childGridView);
            Controls.Add(parentGridView);
            Margin = new Padding(2, 3, 2, 3);
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