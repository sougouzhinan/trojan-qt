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
  explicit ConfigEditor(QWidget *parent = nullptr);

public slots:
  void switchMode(const Config::RunType &t);

private:
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
  QLineEdit *ssl_cipher_le;
  QLineEdit *ssl_server_name_indication_le;
  QLineEdit *ssl_alpn_le;
  QCheckBox *ssl_reuse_session_check;
  QLineEdit *ssl_curves_le;
  QLineEdit *ssl_sig_algorithm_le;

  QCheckBox *tcp_keep_alive_check;
  QCheckBox *tcp_no_delay_check;
  QCheckBox *tcp_fast_open_check;
  QSpinBox *tcp_fast_open_queue_length_box;

  QFormLayout *general_form_layout;
  QFormLayout *ssl_form_layout;
  QFormLayout *tcp_form_layout;

};

#endif // CONFIGEDITOR_H
