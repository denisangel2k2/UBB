namespace MusicalLab2
{
    partial class Form2
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
            label1 = new Label();
            insertButton = new Button();
            statusLabel = new Label();
            flowLayoutPanel1 = new FlowLayoutPanel();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("Segoe UI", 15.75F, FontStyle.Bold, GraphicsUnit.Point);
            label1.Location = new Point(165, 25);
            label1.Margin = new Padding(5, 0, 5, 0);
            label1.Name = "label1";
            label1.Size = new Size(122, 50);
            label1.TabIndex = 0;
            label1.Text = "Insert";
            label1.Click += label1_Click;
            // 
            // insertButton
            // 
            insertButton.Location = new Point(165, 535);
            insertButton.Margin = new Padding(5, 6, 5, 6);
            insertButton.Name = "insertButton";
            insertButton.Size = new Size(129, 46);
            insertButton.TabIndex = 8;
            insertButton.Text = "Insert";
            insertButton.UseVisualStyleBackColor = true;
            insertButton.Click += insertButton_Click;
            // 
            // statusLabel
            // 
            statusLabel.AutoSize = true;
            statusLabel.ForeColor = Color.Red;
            statusLabel.Location = new Point(195, 166);
            statusLabel.Margin = new Padding(5, 0, 5, 0);
            statusLabel.Name = "statusLabel";
            statusLabel.Size = new Size(0, 30);
            statusLabel.TabIndex = 9;
            // 
            // flowLayoutPanel1
            // 
            flowLayoutPanel1.Location = new Point(37, 78);
            flowLayoutPanel1.Name = "flowLayoutPanel1";
            flowLayoutPanel1.Size = new Size(446, 423);
            flowLayoutPanel1.TabIndex = 11;
            // 
            // Form2
            // 
            AutoScaleDimensions = new SizeF(12F, 30F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(507, 613);
            Controls.Add(flowLayoutPanel1);
            Controls.Add(statusLabel);
            Controls.Add(insertButton);
            Controls.Add(label1);
            Margin = new Padding(5, 6, 5, 6);
            Name = "Form2";
            Text = "Form2";
            Load += Form2_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Button insertButton;
        private Label statusLabel;
        private FlowLayoutPanel flowLayoutPanel1;
    }
}