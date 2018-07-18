#include "ConfigEditor.h"

ConfigEditor::ConfigEditor(const Config::RunType &t, QWidget *parent)
  : QWidget(parent)
  , run_type(t)
{
  QLabel *general_label = new QLabel("General", this);
  general_form_layout = new QFormLayout();
  QLabel *ssl_label = new QLabel("SSL Options", this);
  ssl_form_layout = new QFormLayout();
  QLabel *tcp_label = new QLabel("TCP Options", this);
  tcp_form_layout = new QFormLayout();

  switch (t) {
    case Config::RunType::CLIENT:
      {
        local_addr_le = new QLineEdit("127.0.0.1", this);
        local_port_le = new QLineEdit("1080", this);
        remote_addr_le = new QLineEdit(this);
        remote_port_le = new QLineEdit(this);
        passwd_le = new QLineEdit(this);
        append_payload_check = new QCheckBox(this);
        log_level_combo = new QComboBox(this);
        ssl_verify_check = new QCheckBox(this);
        ssl_verify_hostname_check = new QCheckBox(this);
        ssl_cert_path_le = new QLineEdit(this);
        ssl_cipher_le = new QLineEdit(this);
        ssl_server_name_indication_le = new QLineEdit(this);
        ssl_alpn_le = new QLineEdit(this);
        ssl_reuse_session_check = new QCheckBox(this);
        ssl_curves_le = new QLineEdit(this);
        ssl_sig_algorithm_le = new QLineEdit(this);
        tcp_keep_alive_check = new QCheckBox(this);
        tcp_no_delay_check = new QCheckBox(this);
        tcp_fast_open_check = new QCheckBox(this);
        tcp_fast_open_queue_length_box = new QSpinBox(this);

        remote_addr_le->setPlaceholderText("0.0.0.0");
        remote_port_le->setText("443");
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
        ssl_cipher_le->setText("ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:DHE-RSA-AES128-GCM-SHA256:DHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA256:ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES128-SHA:ECDHE-ECDSA-AES256-SHA384:ECDHE-ECDSA-AES256-SHA:ECDHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA256:DHE-RSA-AES128-SHA:DHE-RSA-AES256-SHA256:DHE-RSA-AES256-SHA:ECDHE-ECDSA-DES-CBC3-SHA:ECDHE-RSA-DES-CBC3-SHA:EDH-RSA-DES-CBC3-SHA:AES128-GCM-SHA256:AES256-GCM-SHA384:AES128-SHA256:AES256-SHA256:AES128-SHA:AES256-SHA:DES-CBC3-SHA:!DSS");
        ssl_server_name_indication_le->setPlaceholderText("example.com");
        ssl_alpn_le->setText("h2,http/1.1");
        ssl_reuse_session_check->setChecked(true);
        tcp_keep_alive_check->setChecked(true);
        tcp_no_delay_check->setChecked(true);
        tcp_fast_open_check->setChecked(true);
        tcp_fast_open_queue_length_box->setValue(5);
        tcp_fast_open_queue_length_box->setMinimumWidth(140); //! to align properly

        general_form_layout->setLabelAlignment(Qt::AlignLeading);
        general_form_layout->addRow("local address", local_addr_le);
        general_form_layout->addRow("local port", local_port_le);
        general_form_layout->addRow("remote address", remote_addr_le);
        general_form_layout->addRow("remote port", remote_port_le);
        general_form_layout->addRow("password", passwd_le);
        general_form_layout->addRow("append payload", append_payload_check);
        general_form_layout->addRow("log level", log_level_combo);

        ssl_form_layout->setLabelAlignment(Qt::AlignLeading);
        ssl_form_layout->addRow("verify", ssl_verify_check);
        ssl_form_layout->addRow("verify hostname", ssl_verify_hostname_check);
        ssl_form_layout->addRow("certificate path", ssl_cert_path_le);
        ssl_form_layout->addRow("cipher", ssl_cipher_le);
        ssl_form_layout->addRow("server name indication", ssl_server_name_indication_le);
        ssl_form_layout->addRow("ALPN (comma separation)", ssl_alpn_le);
        ssl_form_layout->addRow("reuse session", ssl_reuse_session_check);
        ssl_form_layout->addRow("curve", ssl_curves_le);
        ssl_form_layout->addRow("signature algorithm", ssl_sig_algorithm_le);

        tcp_form_layout->setLabelAlignment(Qt::AlignLeading);
        tcp_form_layout->addRow("keep alive", tcp_keep_alive_check);
        tcp_form_layout->addRow("no delay", tcp_no_delay_check);
        tcp_form_layout->addRow("fast open", tcp_fast_open_check);
        tcp_form_layout->addRow("fast open queue length", tcp_fast_open_queue_length_box);

        connect(ssl_verify_check, &QCheckBox::toggled, [this](bool toggled) {
            ssl_verify_hostname_check->setEnabled(toggled);
            ssl_cert_path_le->setEnabled(toggled);
          });

        break;
      }
    case Config::RunType::SERVER:
      {
        local_addr_le = new QLineEdit("127.0.0.1", this);
        local_port_le = new QLineEdit("1080", this);
        remote_addr_le = new QLineEdit(this);
        remote_port_le = new QLineEdit(this);
        passwd_le = new QLineEdit(this);
        log_level_combo = new QComboBox(this);
        ssl_cert_path_le = new QLineEdit(this);
        ssl_private_key_path_le = new QLineEdit(this);
        ssl_private_key_password_le = new QLineEdit(this);
        ssl_cipher_le = new QLineEdit(this);
        ssl_prefer_server_cipher_check = new QCheckBox(this);
        ssl_alpn_le = new QLineEdit(this);
        ssl_reuse_session_check = new QCheckBox(this);
        ssl_session_timeout_box = new QSpinBox(this);
        ssl_curves_le = new QLineEdit(this);
        ssl_sig_algorithm_le = new QLineEdit(this);
        ssl_dh_parameters_path_le = new QLineEdit(this);
        tcp_keep_alive_check = new QCheckBox(this);
        tcp_no_delay_check = new QCheckBox(this);
        tcp_fast_open_check = new QCheckBox(this);
        tcp_fast_open_queue_length_box = new QSpinBox(this);

        local_addr_le->setText("0.0.0.0");
        local_port_le->setText("443");
        remote_addr_le->setText("127.0.0.1");
        remote_port_le->setText("80");
        passwd_le->setEchoMode(QLineEdit::Password);
        passwd_le->setPlaceholderText("••••••••");
        log_level_combo->addItem("off");
        log_level_combo->addItem("verbose");
        log_level_combo->addItem("information");
        log_level_combo->addItem("warnings");
        log_level_combo->addItem("errors");
        log_level_combo->addItem("fatal");
        log_level_combo->setCurrentIndex(0);
        ssl_cert_path_le->setPlaceholderText("/path/to/cert.crt");
        ssl_cipher_le->setText("ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES256-SHA:ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES128-SHA:ECDHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA:DHE-RSA-AES256-SHA:AES128-SHA:AES256-SHA:DES-CBC3-SHA");
        ssl_prefer_server_cipher_check->setChecked(true);
        ssl_alpn_le->setText("http/1.1");
        ssl_reuse_session_check->setChecked(true);
        ssl_session_timeout_box->setMaximum(65535);
        ssl_session_timeout_box->setValue(300);
        ssl_session_timeout_box->setMinimumWidth(140);
        tcp_keep_alive_check->setChecked(true);
        tcp_no_delay_check->setChecked(true);
        tcp_fast_open_check->setChecked(true);
        tcp_fast_open_queue_length_box->setValue(5);
        tcp_fast_open_queue_length_box->setMinimumWidth(140); //! to align properly

        general_form_layout->setLabelAlignment(Qt::AlignLeading);
        general_form_layout->addRow("local address", local_addr_le);
        general_form_layout->addRow("local port", local_port_le);
        general_form_layout->addRow("remote address", remote_addr_le);
        general_form_layout->addRow("remote port", remote_port_le);
        general_form_layout->addRow("password", passwd_le);
        general_form_layout->addRow("log level", log_level_combo);

        ssl_form_layout->setLabelAlignment(Qt::AlignLeading);
        ssl_form_layout->addRow("certificate path", ssl_cert_path_le);
        ssl_form_layout->addRow("private key path", ssl_private_key_path_le);
        ssl_form_layout->addRow("private key password", ssl_private_key_password_le);
        ssl_form_layout->addRow("cipher", ssl_cipher_le);
        ssl_form_layout->addRow("prefer server cipher", ssl_prefer_server_cipher_check);
        ssl_form_layout->addRow("ALPN", ssl_alpn_le);
        ssl_form_layout->addRow("reuse session", ssl_reuse_session_check);
        ssl_form_layout->addRow("session timeout", ssl_session_timeout_box);
        ssl_form_layout->addRow("curve", ssl_curves_le);
        ssl_form_layout->addRow("signature algorithm", ssl_sig_algorithm_le);
        ssl_form_layout->addRow("DH parameters path", ssl_dh_parameters_path_le);

        tcp_form_layout->setLabelAlignment(Qt::AlignLeading);
        tcp_form_layout->addRow("keep alive", tcp_keep_alive_check);
        tcp_form_layout->addRow("no delay", tcp_no_delay_check);
        tcp_form_layout->addRow("fast open", tcp_fast_open_check);
        tcp_form_layout->addRow("fast open queue length", tcp_fast_open_queue_length_box);

        break;
      }
    default:
      break;
    }



  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setAlignment(Qt::AlignLeading);
  main_layout->setMargin(30);
  main_layout->addWidget(general_label);
  main_layout->addLayout(general_form_layout);
  main_layout->addWidget(ssl_label);
  main_layout->addLayout(ssl_form_layout);
  main_layout->addWidget(tcp_label);
  main_layout->addLayout(tcp_form_layout);



  QPalette palette(this->palette());
  palette.setColor(QPalette::Foreground, QColor(120,120,120));
  palette.setColor(QPalette::Window, QColor(250,250,250));
  this->setPalette(palette);
  this->setAutoFillBackground(true);

}

Config::RunType ConfigEditor::getConfigType()
{
  return run_type;
}

