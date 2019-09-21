// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "google/cloud/spanner/internal/instance_admin_metadata.h"
#include "google/cloud/spanner/internal/api_client_header.h"
#include "google/cloud/spanner/testing/mock_instance_admin_stub.h"
#include "google/cloud/spanner/testing/validate_metadata.h"
#include "google/cloud/testing_util/assert_ok.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace spanner {
inline namespace SPANNER_CLIENT_NS {
namespace internal {
namespace {

using ::testing::_;
using ::testing::Invoke;
namespace gcsa = google::spanner::admin::instance::v1;

class InstanceAdminMetadataTest : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_ = std::make_shared<spanner_testing::MockInstanceAdminStub>();
    InstanceAdminMetadata stub(mock_);
    expected_api_client_header_ = ApiClientHeader();
  }

  void TearDown() override {}

  Status TransientError() {
    return Status(StatusCode::kUnavailable, "try-again");
  }

  std::shared_ptr<spanner_testing::MockInstanceAdminStub> mock_;
  std::string expected_api_client_header_;
};

TEST_F(InstanceAdminMetadataTest, GetInstance) {
  EXPECT_CALL(*mock_, GetInstance(_, _))
      .WillOnce(Invoke([this](grpc::ClientContext& context,
                              gcsa::GetInstanceRequest const&) {
        EXPECT_STATUS_OK(spanner_testing::IsContextMDValid(
            context,
            "google.spanner.admin.instance.v1.InstanceAdmin."
            "GetInstance",
            expected_api_client_header_));
        return TransientError();
      }));

  InstanceAdminMetadata stub(mock_);
  grpc::ClientContext context;
  gcsa::GetInstanceRequest request;
  request.set_name(
      "projects/test-project-id/"
      "instances/test-instance-id");
  auto response = stub.GetInstance(context, request);
  EXPECT_EQ(TransientError(), response.status());
}

TEST_F(InstanceAdminMetadataTest, ListInstances) {
  EXPECT_CALL(*mock_, ListInstances(_, _))
      .WillOnce(Invoke([this](grpc::ClientContext& context,
                              gcsa::ListInstancesRequest const&) {
        EXPECT_STATUS_OK(spanner_testing::IsContextMDValid(
            context,
            "google.spanner.admin.instance.v1.InstanceAdmin."
            "ListInstances",
            expected_api_client_header_));
        return TransientError();
      }));

  InstanceAdminMetadata stub(mock_);
  grpc::ClientContext context;
  gcsa::ListInstancesRequest request;
  request.set_parent("projects/test-project-id");
  auto response = stub.ListInstances(context, request);
  EXPECT_EQ(TransientError(), response.status());
}

TEST_F(InstanceAdminMetadataTest, GetIamPolicy) {
  EXPECT_CALL(*mock_, GetIamPolicy(_, _))
      .WillOnce(Invoke([this](grpc::ClientContext& context,
                              google::iam::v1::GetIamPolicyRequest const&) {
        EXPECT_STATUS_OK(spanner_testing::IsContextMDValid(
            context,
            "google.spanner.admin.instance.v1.InstanceAdmin."
            "GetIamPolicy",
            expected_api_client_header_));
        return TransientError();
      }));

  InstanceAdminMetadata stub(mock_);
  grpc::ClientContext context;
  google::iam::v1::GetIamPolicyRequest request;
  request.set_resource("projects/test-project-id/instances/test-instance-id");

  auto response = stub.GetIamPolicy(context, request);
  EXPECT_EQ(TransientError(), response.status());
}

TEST_F(InstanceAdminMetadataTest, SetIamPolicy) {
  EXPECT_CALL(*mock_, SetIamPolicy(_, _))
      .WillOnce(Invoke([this](grpc::ClientContext& context,
                              google::iam::v1::SetIamPolicyRequest const&) {
        EXPECT_STATUS_OK(spanner_testing::IsContextMDValid(
            context,
            "google.spanner.admin.instance.v1.InstanceAdmin."
            "SetIamPolicy",
            expected_api_client_header_));
        return TransientError();
      }));

  InstanceAdminMetadata stub(mock_);
  grpc::ClientContext context;
  google::iam::v1::SetIamPolicyRequest request;
  request.set_resource("projects/test-project-id/instances/test-instance-id");
  auto response = stub.SetIamPolicy(context, request);
  EXPECT_EQ(TransientError(), response.status());
}

TEST_F(InstanceAdminMetadataTest, TestIamPermissions) {
  EXPECT_CALL(*mock_, TestIamPermissions(_, _))
      .WillOnce(
          Invoke([this](grpc::ClientContext& context,
                        google::iam::v1::TestIamPermissionsRequest const&) {
            EXPECT_STATUS_OK(spanner_testing::IsContextMDValid(
                context,
                "google.spanner.admin.instance.v1.InstanceAdmin."
                "TestIamPermissions",
                expected_api_client_header_));
            return TransientError();
          }));

  InstanceAdminMetadata stub(mock_);
  grpc::ClientContext context;
  google::iam::v1::TestIamPermissionsRequest request;
  request.set_resource("projects/test-project-id/instances/test-instance-id");
  auto response = stub.TestIamPermissions(context, request);
  EXPECT_EQ(TransientError(), response.status());
}

}  // namespace
}  // namespace internal
}  // namespace SPANNER_CLIENT_NS
}  // namespace spanner
}  // namespace cloud
}  // namespace google