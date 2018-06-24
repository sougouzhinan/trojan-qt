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
  , tcp_keep_alive_check(new QCheckBox(this))
  , tcp_no_delay_check(new QCheckBox(this))
  , tcp_fast_open_check(new QCheckBox(this))
  , tcp_fast_open_queue_length_box(new QSpinBox(this))
{
  remote_addr_le->setPlaceholderText("0.0.0.0");
  remote_port_le->setPlaceholderText("443");
  passwd_le->setEchoMode(QLineEdit::Password);
  passwd_le->setPlaceholderText("••••••••");
  append_payload_check->setChecked(true);
  append_payload_check->setHidden(true);
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
  tcp_fast_open_queue_length_box->setValue(5);
  tcp_fast_open_queue_length_box->setMinimumWidth(140); //! to align properly

  QLabel *general_label = new QLabel("General", this);
  general_form_layout = new QFormLayout();
  general_form_layout->setLabelAlignment(Qt::AlignLeading);
  general_form_layout->insertRow(0, "local address", local_addr_le);
  general_form_layout->insertRow(1, "local port", local_port_le);
  general_form_layout->insertRow(2, "remote address", remote_addr_le);
  general_form_layout->insertRow(3, "remote port", remote_port_le);
  general_form_layout->insertRow(4, "password", passwd_le);
  general_form_layout->insertRow(5, "append payload", append_payload_check);
  general_form_layout->insertRow(6, "log level", log_level_combo);

  QLabel *ssl_label = new QLabel("SSL Options", this);
  ssl_form_layout = new QFormLayout();
  ssl_form_layout->setLabelAlignment(Qt::AlignLeading);
  ssl_form_layout->insertRow(0, "enable SSL", ssl_verify_check);
  ssl_form_layout->insertRow(1, "verify hostname", ssl_verify_hostname_check);
  ssl_form_layout->insertRow(2, "certificate path", ssl_cert_path_le);
  ssl_form_layout->insertRow(3, "cipher", ssl_cipher_le);
  ssl_form_layout->insertRow(4, "server name indication", ssl_server_name_indication_le);
  ssl_form_layout->insertRow(5, "ALPN", ssl_alpn_le);
  ssl_form_layout->insertRow(6, "reuse session", ssl_reuse_session_check);
  ssl_form_layout->insertRow(7, "curve", ssl_curves_le);
  ssl_form_layout->insertRow(8, "signature algorithm", ssl_sig_algorithm_le);

  QLabel *tcp_label = new QLabel("TCP Options", this);
  tcp_form_layout = new QFormLayout();
  tcp_form_layout->setLabelAlignment(Qt::AlignLeading);
  tcp_form_layout->insertRow(0, "keep alive", tcp_keep_alive_check);
  tcp_form_layout->insertRow(1, "no delay", tcp_no_delay_check);
  tcp_form_layout->insertRow(2, "fast open", tcp_fast_open_check);
  tcp_form_layout->insertRow(3, "fast open queue length", tcp_fast_open_queue_length_box);

  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignLeading);
  main_layout->setMargin(30);
  main_layout->addWidget(general_label);
  main_layout->addLayout(general_form_layout);
  main_layout->addWidget(ssl_label);
  main_layout->addLayout(ssl_form_layout);
  main_layout->addWidget(tcp_label);
  main_layout->addLayout(tcp_form_layout);

  connect(ssl_verify_check, &QCheckBox::toggled, [this](bool toggled) {
      ssl_verify_hostname_check->setEnabled(toggled);
      ssl_cert_path_le->setEnabled(toggled);
    });


  QPalette palette(this->palette());
  palette.setColor(QPalette::Foreground, QColor(120,120,120));
  palette.setColor(QPalette::Window, QColor(250,250,250));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

  this->switchMode(Config::RunType::CLIENT);
}

void ConfigEditor::switchMode(const Config::RunType &t)
{
  if(t == Config::SERVER)
    {
      //! Layout Bug Here
      general_form_layout->insertRow(5, "append payload", append_payload_check);
      append_payload_check->setHidden(false);
    }
  else
    {
      general_form_layout->takeRow(5);
      append_payload_check->setHidden(true);
    }

}
