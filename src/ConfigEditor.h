#ifndef CONFIGEDITOR_H
#define CONFIGEDITOR_H

#include "trojan/src/config.h"

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QFormLayout>
#include <QSpinBox>


class ConfigEditor : public QWidget
{
  Q_OBJECT
public:
  explicit ConfigEditor(const Config::RunType &t, QWidget *parent = nullptr);
  Config::RunType getConfigType();

public slots:

private:
  Config::RunType run_type;

  QLineEdit *local_addr_le;
  QLineEdit *local_port_le;
  QLineEdit *remote_addr_le;
  QLineEdit *remote_port_le;

  QLineEdit *passwd_le;
  QCheckBox *append_payload_check;
  QComboBox *log_level_combo;

  QCheckBox *ssl_verify_check;
  QCheckBox *ssl_verify_hostname_check;

  QLineEdit *ssl_cert_path_le;
  QLineEdit *ssl_private_key_path_le;
  QLineEdit *ssl_private_key_password_le;
  QLineEdit *ssl_cipher_le;
  QLineEdit *ssl_server_name_indication_le;
  QCheckBox *ssl_prefer_server_cipher_check;
  QLineEdit *ssl_alpn_le;
  QCheckBox *ssl_reuse_session_check;
  QSpinBox *ssl_session_timeout_box;
  QLineEdit *ssl_curves_le;
  QLineEdit *ssl_sig_algorithm_le;
  QLineEdit *ssl_dh_parameters_path_le;

  QCheckBox *tcp_keep_alive_check;
  QCheckBox *tcp_no_delay_check;
  QCheckBox *tcp_fast_open_check;
  QSpinBox *tcp_fast_open_queue_length_box;

  QFormLayout *general_form_layout;
  QFormLayout *ssl_form_layout;
  QFormLayout *tcp_form_layout;

};

#endif // CONFIGEDITOR_H
