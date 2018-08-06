#include "ConfigEditor.h"

ConfigEditor::ConfigEditor(const Config::RunType &t, QWidget *parent)
  : QWidget(parent)
  , run_type(t)
{
  QLabel *general_label = new QLabel("<b>General</b>", this);
  general_form_layout = new QFormLayout();
  QLabel *ssl_label = new QLabel("<b>SSL Options</b>", this);
  ssl_form_layout = new QFormLayout();
  QLabel *tcp_label = new QLabel("<b>TCP Options</b>", this);
  tcp_form_layout = new QFormLayout();

  local_addr_le = new QLineEdit("127.0.0.1", this);
  local_port_le = new QLineEdit("1080", this);
  remote_addr_le = new QLineEdit(this);
  remote_port_le = new QLineEdit(this);
  passwd_le = new QLineEdit(this);
  passwd_le->setPlaceholderText("••••••••");
  log_level_combo = new QComboBox(this);
  log_level_combo->addItem("all", 0);
  log_level_combo->addItem("information", 1);
  log_level_combo->addItem("warnings", 2);
  log_level_combo->addItem("errors", 3);
  log_level_combo->addItem("fatal", 4);
  log_level_combo->addItem("off", 5);
  log_level_combo->setCurrentIndex(0);
  ssl_cert_path_le = new QLineEdit(this);
  ssl_cipher_le = new QLineEdit(this);
  ssl_curves_le = new QLineEdit(this);
  ssl_sig_algorithm_le = new QLineEdit(this);
  ssl_alpn_le = new QLineEdit(this);
  ssl_reuse_session_check = new QCheckBox(this);
  ssl_reuse_session_check->setChecked(true);
  tcp_keep_alive_check = new QCheckBox(this);
  tcp_keep_alive_check->setChecked(true);
  tcp_no_delay_check = new QCheckBox(this);
  tcp_no_delay_check->setChecked(true);
  tcp_fast_open_check = new QCheckBox(this);
  tcp_fast_open_check->setChecked(true);
  tcp_fast_open_queue_length_box = new QSpinBox(this);
  tcp_fast_open_queue_length_box->setValue(5);
  tcp_fast_open_queue_length_box->setMinimumWidth(140); //! to align properly

  general_form_layout->setLabelAlignment(Qt::AlignLeading);
  general_form_layout->addRow("local address", local_addr_le);
  general_form_layout->addRow("local port", local_port_le);
  general_form_layout->addRow("remote address", remote_addr_le);
  general_form_layout->addRow("remote port", remote_port_le);
  general_form_layout->addRow("password", passwd_le);
  general_form_layout->addRow("log level", log_level_combo);

  tcp_form_layout->setLabelAlignment(Qt::AlignLeading);
  tcp_form_layout->addRow("keep alive", tcp_keep_alive_check);
  tcp_form_layout->addRow("no delay", tcp_no_delay_check);
  tcp_form_layout->addRow("fast open", tcp_fast_open_check);
  tcp_form_layout->addRow("fast open queue length", tcp_fast_open_queue_length_box);

  switch (t) {
    case Config::RunType::CLIENT:
      {

        remote_addr_le->setPlaceholderText("0.0.0.0");
        remote_port_le->setText("443");
        passwd_le->setEchoMode(QLineEdit::Password);
        append_payload_check = new QCheckBox(this);
        append_payload_check->setChecked(true);
        ssl_verify_check = new QCheckBox(this);
        ssl_verify_check->setChecked(true);
        ssl_verify_hostname_check = new QCheckBox(this);
        ssl_verify_hostname_check->setChecked(true);
        ssl_cert_path_le->setPlaceholderText("/path/to/cert.crt");
        ssl_cipher_le->setText("ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:DHE-RSA-AES128-GCM-SHA256:DHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA256:ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES128-SHA:ECDHE-ECDSA-AES256-SHA384:ECDHE-ECDSA-AES256-SHA:ECDHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA256:DHE-RSA-AES128-SHA:DHE-RSA-AES256-SHA256:DHE-RSA-AES256-SHA:ECDHE-ECDSA-DES-CBC3-SHA:ECDHE-RSA-DES-CBC3-SHA:EDH-RSA-DES-CBC3-SHA:AES128-GCM-SHA256:AES256-GCM-SHA384:AES128-SHA256:AES256-SHA256:AES128-SHA:AES256-SHA:DES-CBC3-SHA:!DSS");
        ssl_server_name_indication_le = new QLineEdit(this);
        ssl_server_name_indication_le->setPlaceholderText("example.com");
        ssl_alpn_le->setText("h2,http/1.1");

        general_form_layout->addRow("append payload", append_payload_check);

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

        connect(ssl_verify_check, &QCheckBox::toggled, [this](bool toggled) {
            ssl_verify_hostname_check->setEnabled(toggled);
            ssl_cert_path_le->setEnabled(toggled);
          });

        break;
      }
    case Config::RunType::SERVER:
      {

        local_addr_le->setText("0.0.0.0");
        local_port_le->setText("443");
        remote_addr_le->setText("127.0.0.1");
        remote_port_le->setText("80");
        ssl_private_key_path_le = new QLineEdit(this);
        ssl_private_key_password_le = new QLineEdit(this);
        ssl_cert_path_le->setPlaceholderText("/path/to/cert.crt");
        ssl_cipher_le->setText("ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES256-SHA:ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES128-SHA:ECDHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA:DHE-RSA-AES256-SHA:AES128-SHA:AES256-SHA:DES-CBC3-SHA");
        ssl_prefer_server_cipher_check = new QCheckBox(this);
        ssl_prefer_server_cipher_check->setChecked(true);
        ssl_alpn_le->setText("http/1.1");
        ssl_session_timeout_box = new QSpinBox(this);
        ssl_session_timeout_box->setMaximum(65535);
        ssl_session_timeout_box->setValue(300);
        ssl_session_timeout_box->setMinimumWidth(140);
        ssl_dh_parameters_path_le = new QLineEdit(this);

        // It doesn't make sense to split this part, because some lines are grouped together.
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

        break;
      }
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

QJsonObject ConfigEditor::getJson()
{
  QJsonObject r;
  r.insert("local_addr", local_addr_le->text());
  r.insert("local_port", local_port_le->text());
  r.insert("remote_addr", remote_addr_le->text());
  r.insert("remote_port", remote_port_le->text());
  r.insert("log_level", log_level_combo->currentData().toInt());

  QJsonObject sslObj;
  sslObj.insert("cert", ssl_cert_path_le->text());
  sslObj.insert("cipher", ssl_cipher_le->text());
  sslObj.insert("reuse_session", ssl_reuse_session_check->isChecked());
  sslObj.insert("curves", ssl_curves_le->text());
  sslObj.insert("sigalgs", ssl_sig_algorithm_le->text());
  QJsonArray alpnArray;
  for(QString s : ssl_alpn_le->text().split(","))
    alpnArray.append(s.trimmed());
  sslObj.insert("alpn", alpnArray);

  QJsonObject tcpObj;
  tcpObj.insert("keep_alive", tcp_keep_alive_check->isChecked());
  tcpObj.insert("no_delay", tcp_no_delay_check->isChecked());
  tcpObj.insert("fast_open", tcp_fast_open_check->isChecked());
  tcpObj.insert("fast_open_qlen", tcp_fast_open_queue_length_box->value());

  switch (run_type) {
    case Config::RunType::CLIENT:
      {
        r.insert("run_type", "client");
        r.insert("append_payload", append_payload_check->isChecked());
        sslObj.insert("verify", ssl_verify_check->isChecked());
        sslObj.insert("verify_hostname", ssl_verify_hostname_check->isChecked());
        sslObj.insert("sni", ssl_server_name_indication_le->text());
        QJsonArray passwordArray;
        passwordArray.append(passwd_le->text());
        r.insert("password", passwordArray);
        break;
      }
    case Config::RunType::SERVER:
      {
        r.insert("run_type", "server");
        QJsonArray pswdArray;
        for(QString s : passwd_le->text().split(","))
            pswdArray.append(s.trimmed());
        r.insert("password", pswdArray);
        sslObj.insert("key", ssl_private_key_path_le->text());
        sslObj.insert("key_password", ssl_private_key_password_le->text());
        sslObj.insert("prefer_server_cipher", ssl_prefer_server_cipher_check->isChecked());
        sslObj.insert("session_timeout", ssl_session_timeout_box->value());
        sslObj.insert("dhparam", ssl_dh_parameters_path_le->text());
        break;
      }
    }
  r.insert("ssl", sslObj);
  r.insert("tcp", tcpObj);

  return r;
}

void ConfigEditor::setJson(QJsonObject &obj)
{
  local_addr_le->setText(obj["local_addr"].toString());
  local_port_le->setText(obj["local_port"].toString());
  remote_addr_le->setText(obj["remote_addr"].toString());
  remote_port_le->setText(obj["remote_port"].toString());
  log_level_combo->setCurrentIndex(obj["log_level"].toInt());

  QString pswdStr = "";
  for(QJsonValue v : obj["password"].toArray())
    pswdStr.append(v.toString() + ",");
  passwd_le->setText(pswdStr.left(pswdStr.size() - 1));

  QJsonObject sslObj = obj["ssl"].toObject();
  ssl_cert_path_le->setText(sslObj["cert"].toString());
  ssl_cipher_le->setText(sslObj["cipher"].toString());
  ssl_reuse_session_check->setChecked(sslObj["reuse_session"].toBool());
  ssl_curves_le->setText(sslObj["curves"].toString());
  ssl_sig_algorithm_le->setText(sslObj["sigalgs"].toString());

  QString alpnStr = "";
  for(QJsonValue v : sslObj["alpn"].toArray())
    alpnStr.append(v.toString() + ",");
  ssl_alpn_le->setText(alpnStr.left(alpnStr.size() - 1));

  QJsonObject tcpObj = obj["tcp"].toObject();
  tcp_keep_alive_check->setChecked(tcpObj["keep_alive"].toBool());
  tcp_no_delay_check->setChecked(tcpObj["no_delay"].toBool());
  tcp_fast_open_check->setChecked(tcpObj["fast_open"].toBool());
  tcp_fast_open_queue_length_box->setValue(tcpObj["fast_open_qlen"].toInt());

  switch (run_type) {
    case Config::RunType::CLIENT:
      {

        append_payload_check->setChecked(obj["append_payload"].toBool());
        ssl_verify_check->setChecked(sslObj["verify"].toBool());
        ssl_verify_hostname_check->setChecked(sslObj["verify_hostname"].toBool());
        ssl_server_name_indication_le->setText(sslObj["sni"].toString());
        break;
      }
    case Config::RunType::SERVER:
      {
        ssl_private_key_path_le->setText(sslObj["key"].toString());
        ssl_private_key_password_le->setText(sslObj["key_password"].toString());
        ssl_prefer_server_cipher_check->setChecked(sslObj["prefer_server_cipher"].toBool());
        ssl_session_timeout_box->setValue(sslObj["session_timeout"].toInt());
        ssl_dh_parameters_path_le->setText(sslObj["dhparam"].toString());
        break;
      }
    }
}

