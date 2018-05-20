#include "ConfigEditor.h"

ConfigEditor::ConfigEditor(QWidget *parent)
  : QWidget(parent)
  , local_addr_le(new QLineEdit("127.0.0.1", this))
  , local_port_le(new QLineEdit("1080", this))
  , remote_addr_le(new QLineEdit(this))
  , remote_port_le(new QLineEdit(this))
  , passwd_le(new QLineEdit(this))
  , append_payload_check(new QCheckBox(this))
  , log_level_combo(new QComboBox(this))
  , ssl_verify_check(new QCheckBox(this))
  , ssl_verify_hostname_check(new QCheckBox(this))
  , ssl_cert_path_le(new QLineEdit(this))
  , ssl_cipher_le(new QLineEdit(this))
  , ssl_server_name_indication_le(new QLineEdit(this))
  , ssl_alpn_le(new QLineEdit(this))
  , ssl_reuse_session_check(new QCheckBox(this))
  , ssl_curves_le(new QLineEdit(this))
  , ssl_sig_algorithm_le(new QLineEdit(this))
{
  remote_addr_le->setPlaceholderText("0.0.0.0");
  remote_port_le->setPlaceholderText("443");
  passwd_le->setEchoMode(QLineEdit::Password);
  passwd_le->setPlaceholderText("••••••••");
  append_payload_check->setChecked(true);
  log_level_combo->addItem("off");
  log_level_combo->addItem("verbose");
  log_level_combo->addItem("information");
  log_level_combo->addItem("warnings");
  log_level_combo->addItem("errors");
  log_level_combo->addItem("fatal");
  log_level_combo->setCurrentIndex(0);
  ssl_verify_check->setChecked(true);
  ssl_verify_hostname_check->setChecked(true);
  ssl_cert_path_le->setPlaceholderText("/path/to/cert.crt");
  ssl_server_name_indication_le->setPlaceholderText("example.com");
  ssl_reuse_session_check->setChecked(true);

  QLabel *general_label = new QLabel("General", this);
  QFormLayout *general_form_layout = new QFormLayout();
  general_form_layout->addRow("local address", local_addr_le);
  general_form_layout->addRow("local port", local_port_le);
  general_form_layout->addRow("remote address", remote_addr_le);
  general_form_layout->addRow("remote port", remote_port_le);
  general_form_layout->addRow("password", passwd_le);
  general_form_layout->addRow("append payload", append_payload_check);
  general_form_layout->addRow("log level", log_level_combo);

  QLabel *ssl_label = new QLabel("SSL Options", this);
  QFormLayout *ssl_form_layout = new QFormLayout();
  ssl_form_layout->addRow("enable SSL", ssl_verify_check);
  ssl_form_layout->addRow("verify hostname", ssl_verify_hostname_check);
  ssl_form_layout->addRow("certificate path", ssl_cert_path_le);
  ssl_form_layout->addRow("cipher", ssl_cipher_le);
  ssl_form_layout->addRow("server name indication", ssl_server_name_indication_le);
  ssl_form_layout->addRow("ALPN", ssl_alpn_le);
  ssl_form_layout->addRow("reuse session", ssl_reuse_session_check);
  ssl_form_layout->addRow("curve", ssl_curves_le);
  ssl_form_layout->addRow("signature algorithm", ssl_sig_algorithm_le);

  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setMargin(30);
  main_layout->addWidget(general_label);
  main_layout->addLayout(general_form_layout);
  main_layout->addWidget(ssl_label);
  main_layout->addLayout(ssl_form_layout);

  connect(ssl_verify_check, &QCheckBox::toggled, [this](bool toggled) {
      ssl_verify_hostname_check->setEnabled(toggled);
      ssl_cert_path_le->setEnabled(toggled);
    });


  QPalette palette(this->palette());
  palette.setColor(QPalette::Foreground, QColor(120,120,120));
  palette.setColor(QPalette::Window, QColor(250,250,250));
  this->setPalette(palette);
  this->setAutoFillBackground(true);
  this->setMinimumSize(QSize(450,0));
}
